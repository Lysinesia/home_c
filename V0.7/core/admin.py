from django.contrib import admin
from .models import Equipment, Task, TaskCompletion

@admin.register(Task)
class TaskAdmin(admin.ModelAdmin):
    readonly_fields = ('completed_at',)
    list_display = ('title', 'equipment', 'due_date', 'status')
    list_filter = ('status',)

@admin.register(Equipment)
class EquipmentAdmin(admin.ModelAdmin):
    list_display = ('name', 'location', 'is_active')
    list_filter = ('is_active',)
    search_fields = ('name', 'location')


@admin.register(TaskCompletion)
class TaskCompletionAdmin(admin.ModelAdmin):
    list_display = ('task', 'completed_by', 'completed_at')
