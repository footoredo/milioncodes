@echo off
set str=2262 Goldbach's Conjecture.7z
echo %str:~0,-3%
FOR %%i in (*.7z) do (
	set filename=%%i
	echo %filename%
)
pause