# pylint: skip-file
from django.contrib.auth.decorators import login_required
from django.contrib.admin.views.decorators import staff_member_required
from django.utils import timezone
from datetime import timedelta
from .models import Task, TaskCompletion
from django.shortcuts import render, redirect, get_object_or_404
from core.models import TaskCompletion
from django.contrib.auth.decorators import user_passes_test
from django.contrib.auth.models import User, Group
from core.models import Equipment
from django.contrib.auth import logout


def logout_view(request):
    logout(request)
    return redirect('login')


@login_required
def dashboard(request):
    now = timezone.now()

    tasks = (
        Task.objects.filter(status='active')
        |
        Task.objects.filter(
            status='completed',
            completed_at__gte=now - timedelta(minutes=1)
        )
    ).order_by('due_date')

    return render(request, 'dashboard.html', {
        'tasks': tasks,
        'now': now,
    })


@staff_member_required
def settings_view(request):
    return render(request, 'settings.html')

@login_required
def calendar_view(request):
    return render(request, 'calendar.html')

@staff_member_required
def employees_view(request):
    return render(request, 'settings/employees.html')


@staff_member_required
def equipment_view(request):
    return render(request, 'settings/equipment.html')


@staff_member_required
def tasks_settings_view(request):
    return render(request, 'settings/tasks_settings.html')


@staff_member_required
def roles_view(request):
    return render(request, 'settings/roles.html')


@login_required
def complete_task(request, task_id):
    if request.method != 'POST':
        return redirect('dashboard')

    task = get_object_or_404(Task, id=task_id)

    if task.status != 'active':
        return redirect('dashboard')

    TaskCompletion.objects.create(
        task=task,
        completed_by=request.user,
        due_date=task.due_date
    )

    task.status = 'completed'
    task.completed_at = timezone.now()
    task.save()

    return redirect('dashboard')

@login_required
def calendar_view(request):
    today = timezone.localdate()

    start_date = today - timedelta(days=7)
    end_date = today + timedelta(days=14)

    # все дни диапазона
    days = []
    current = start_date
    while current <= end_date:
        days.append(current)
        current += timedelta(days=1)

    # задачи ТОЛЬКО активные
    tasks = Task.objects.filter(
        due_date__date__range=(start_date, end_date),
        status='active'
    ).select_related('equipment')

    # группировка задач по дате
    tasks_by_day = {}
    for task in tasks:
        day = task.due_date.date()
        tasks_by_day.setdefault(day, []).append(task)

    return render(request, 'calendar.html', {
        'days': days,
        'tasks_by_day': tasks_by_day,
        'today': today,
    })

@login_required
def history_view(request):
    tasks = Task.objects.all().order_by('-due_date')

    return render(request, 'history.html', {
        'tasks': tasks
    })


#/////////////////////////////employees//////////////////////////////

def is_admin(user):
    return user.is_superuser


@user_passes_test(is_admin)
def employees_view(request):
    if not request.user.is_superuser:
        return redirect('dashboard')

    users = User.objects.all().order_by('username')
    groups = Group.objects.all()

    return render(request, 'settings/employees.html', {
        'users': users,
        'groups': groups
    })

@user_passes_test(is_admin)
def toggle_active(request, user_id):
    user = get_object_or_404(User, id=user_id)
    user.is_active = not user.is_active
    user.save()
    return redirect('employees')


@user_passes_test(is_admin)
def toggle_admin(request, user_id):
    user = get_object_or_404(User, id=user_id)
    user.is_staff = not user.is_staff
    user.save()
    return redirect('employees')


#/////////////////////////////equipment//////////////////////////////

def is_admin(user):
    return user.is_superuser


@user_passes_test(is_admin)
def equipment_view(request):
    equipment = Equipment.objects.all().order_by('name')
    return render(request, 'settings/equipment.html', {
        'equipment': equipment
    })


@user_passes_test(is_admin)
def equipment_add(request):
    if request.method == 'POST':
        name = request.POST.get('name')
        location = request.POST.get('location')

        if name:
            Equipment.objects.create(
                name=name,
                location=location
            )
        return redirect('equipment')

    return render(request, 'settings/equipment_form.html')


@user_passes_test(is_admin)
def equipment_edit(request, eq_id):
    eq = get_object_or_404(Equipment, id=eq_id)

    if request.method == 'POST':
        eq.name = request.POST.get('name')
        eq.location = request.POST.get('location')
        eq.is_active = 'is_active' in request.POST
        eq.save()
        return redirect('equipment')

    return render(request, 'settings/equipment_form.html', {
        'equipment': eq
    })


@user_passes_test(is_admin)
def equipment_delete(request, eq_id):
    eq = get_object_or_404(Equipment, id=eq_id)
    eq.delete()
    return redirect('equipment')

#/////////////////////////////tasks settings//////////////////////////////

@login_required
def tasks_settings_view(request):
    if request.method == 'POST':
        title = request.POST.get('title')
        equipment_id = request.POST.get('equipment')
        due_date = request.POST.get('due_date')

        if title and equipment_id and due_date:
            Task.objects.create(
                title=title,
                equipment_id=equipment_id,
                due_date=due_date,
                status='active'
            )
            return redirect('tasks_settings')

    tasks = Task.objects.all().order_by('-due_date')
    equipment = Equipment.objects.filter(is_active=True)

    return render(request, 'settings/tasks_settings.html', {
        'tasks': tasks,
        'equipment': equipment
    })

#/////////////////////////////roles//////////////////////////////

@login_required
def roles_view(request):
    if not request.user.is_superuser:
        return redirect('dashboard')

    if request.method == 'POST':
        user_id = request.POST.get('user_id')
        group_id = request.POST.get('group_id')

        if user_id:
            user = User.objects.get(id=user_id)
            user.groups.clear()

            if group_id:
                group = Group.objects.get(id=group_id)
                user.groups.add(group)

        return redirect('roles')

    users = User.objects.all().order_by('username')
    groups = Group.objects.all()

    return render(request, 'settings/roles.html', {
        'users': users,
        'groups': groups
    })

@login_required
def employees_view(request):
    if not request.user.is_superuser:
        return redirect('dashboard')

    if request.method == 'POST':
        username = request.POST.get('username')
        password = request.POST.get('password')
        group_id = request.POST.get('group')

        if username and password:
            user = User.objects.create_user(
                username=username,
                password=password
            )

            if group_id:
                group = Group.objects.get(id=group_id)
                user.groups.add(group)

            return redirect('employees')

    users = User.objects.all().order_by('username')
    groups = Group.objects.all()

    return render(request, 'settings/employees.html', {
        'users': users,
        'groups': groups
    })
