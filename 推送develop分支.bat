@echo off
git push origin develop
if not %errorlevel% LEQ 0 (
	COLOR 4
	echo ���ʹ�����������
)
pause