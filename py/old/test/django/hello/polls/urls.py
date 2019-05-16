#import django.urls.path as path
from django.urls import path
from  django.contrib import admin
import views

urlpatterns = ( [
		path('', views.index, name='index'),
	]
)
