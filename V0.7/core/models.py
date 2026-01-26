# pylint: skip-file
from django.db import models
from django.contrib.auth.models import User
from django.utils import timezone


class Equipment(models.Model):
    name = models.CharField(max_length=100, verbose_name='Название')
    location = models.CharField(max_length=100, blank=True, verbose_name='Локация')
    is_active = models.BooleanField(default=True, verbose_name='Активно')

    def __str__(self):
        return self.name


class Task(models.Model):
    STATUS_CHOICES = (
        ('active', 'Активная'),
        ('completed', 'Выполнена'),
    )

    title = models.CharField(max_length=255)
    equipment = models.ForeignKey(Equipment, on_delete=models.CASCADE)
    due_date = models.DateField()
    status = models.CharField(max_length=20, choices=STATUS_CHOICES, default='active')
    completed_at = models.DateTimeField(null=True, blank=True)

    def is_recently_completed(self):
        if not self.completed_at:
            return False
        return timezone.now() - self.completed_at < timezone.timedelta(minutes=1)

    title = models.CharField("Название задачи", max_length=200)
    equipment = models.ForeignKey(
        Equipment,
        on_delete=models.CASCADE,
        related_name='tasks',
        verbose_name="Оборудование"
    )
    due_date = models.DateTimeField("Срок выполнения")
    status = models.CharField(
        "Статус",
        max_length=10,
        choices=STATUS_CHOICES,
        default='active'
    )

    created_at = models.DateTimeField(auto_now_add=True)

    def is_overdue(self):
        return self.status == 'active' and timezone.now() > self.due_date
    def __str__(self):
        return self.title


class TaskCompletion(models.Model):
    task = models.ForeignKey(Task, on_delete=models.CASCADE)
    completed_by = models.ForeignKey(User, on_delete=models.CASCADE)
    completed_at = models.DateTimeField(auto_now_add=True)
    due_date = models.DateField()

    def in_time(self):
        return self.completed_at <= self.due_date
    
    def __str__(self):
        return f"{self.task.title} — {self.completed_by}"
