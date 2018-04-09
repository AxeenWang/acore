@echo off
for /r "." %%a in (*.sdf) do del /a /f /q %%a
for /r "." %%a in (*.aps) do del /a /f /q %%a
for /r "." %%a in (*.db) do del /a /f /q %%a
for /r "." %%a in (*.db) do del /a /f /q %%a
for /r "." %%a in (*.db) do del /a /f /q %%a
for /f "delims=" %%d in ('"dir .vs /ad/b/s | sort /r"') do (rd /s /q "%%d" 2>nul && echo "%%d")
for /f "delims=" %%d in ('"dir relay /ad/b/s | sort /r"') do (rd /s /q "%%d" 2>nul && echo "%%d")
