# pylint: skip-file
from django.urls import path
from django.contrib.auth import views as auth_views
from . import views

urlpatterns = [
    path('', views.dashboard, name='dashboard'),
    path('login/', auth_views.LoginView.as_view(template_name='login.html'), name='login'),
    path('logout/', auth_views.LogoutView.as_view(), name='logout'),
    path('settings/', views.settings_view, name='settings'),
    path('calendar/', views.calendar_view, name='calendar'),
    path('history/', views.history_view, name='history'),
    path('settings/employees/', views.employees_view, name='employees'),
    path('settings/equipment/', views.equipment_view, name='equipment'),
    path('settings/tasks/', views.tasks_settings_view, name='tasks_settings'),
    path('settings/roles/', views.roles_view, name='roles'),
    path('task/<int:task_id>/complete/', views.complete_task, name='complete_task'),
    path('logout/', views.logout_view, name='logout'),
    path('settings/employees/', views.employees_view, name='employees'),
    path('settings/employees/', views.employees_view, name='employees'),
    path('settings/employees/<int:user_id>/toggle-active/', views.toggle_active, name='toggle_active'),
    path('settings/employees/<int:user_id>/toggle-admin/', views.toggle_admin, name='toggle_admin'),
    path('settings/equipment/', views.equipment_view, name='equipment'),
    path('settings/equipment/add/', views.equipment_add, name='equipment_add'),
    path('settings/equipment/<int:eq_id>/edit/', views.equipment_edit, name='equipment_edit'),
    path('settings/equipment/<int:eq_id>/delete/', views.equipment_delete, name='equipment_delete'),
]
