@echo off
title VeloRent Web UI Server (Light Theme 2026)
color 0A
echo =========================================================================
echo   Starting VeloRent Web Server on http://localhost:5500/
echo =========================================================================
echo.
start "" "http://localhost:5500/index.html"
python "%~dp0website\server.py"
pause
