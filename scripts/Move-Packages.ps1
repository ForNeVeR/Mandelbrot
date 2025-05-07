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

$files = Get-ChildItem -Recurse "$SourcePath/**/*.zip"
$files | ForEach-Object {
    $archDir = [IO.Path]::GetDirectoryName($_)
    $osDir = [IO.Path]::GetDirectoryName($archDir)
    $arch = [IO.Path]::GetFileName($archDir)
    $os = [IO.Path]::GetFileName($osDir)
    Move-Item -LiteralPath $_ "$TargetPath/mandelbrot.$os.$arch.zip"
}
