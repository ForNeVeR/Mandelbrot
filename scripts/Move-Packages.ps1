# SPDX-FileCopyrightText: 2025 Friedrich von Never <friedrich@fornever.me>
#
# SPDX-License-Identifier: MIT

param (
    $SourcePath = "$PSScriptRoot/../tmp",
    $TargetPath = "$PSScriptRoot/../package"
)

$ErrorActionPreference = 'Stop'
Set-StrictMode -Version Latest

if (!(Test-Path $TargetPath)) {
    New-Item -Type Directory $TargetPath
}

Get-Item "$SourcePath/*/*" | ForEach-Object {
    $archDir = $_
    $osDir = [IO.Path]::GetDirectoryName($archDir)
    $arch = [IO.Path]::GetFileName($archDir)
    $os = [IO.Path]::GetFileName($osDir)
    $archiveName = "$TargetPath/mandelbrot.$os.$arch.zip"
    Compress-Archive "$_/*" $archiveName
}
