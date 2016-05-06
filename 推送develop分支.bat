@echo off
git push origin develop
if not %errorlevel% LEQ 0 (
	COLOR 4
	echo ÍÆËÍ´íÎó£¬Çë¼ì²éÉèÖÃ
)
pause