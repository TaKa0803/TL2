$files = Get-Item *.jpg
foreach($f in $files){
    Start-Process -FilePath TL2.exe -ArgumentList $f -Wait
}
pause