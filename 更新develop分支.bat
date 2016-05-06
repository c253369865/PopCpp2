@echo off
git fetch origin
git checkout develop
if %errorlevel% LEQ 0 (
	git merge remotes/origin/develop
) else (
	COLOR 4
	echo 分支合并错误，请检查设置
)
pause
