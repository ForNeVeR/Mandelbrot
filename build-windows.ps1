<#
.SYNOPSIS
    Downloads and build the Mandelbrot dependencies and build the program.
.PARAMETER Platform
    Target platform triplet in vcpkg notation. Check `vcpkg help triplet` for
    documentation.
.PARAMETER BuildType
    Either Debug or Release.
.PARAMETER BuildDirectory
    Directory where the files build will be placed.
.PARAMETER VcpkgToolchainFile
    Path to vcpkg toolchain file, see
    https://github.com/Microsoft/vcpkg/blob/master/docs/EXAMPLES.md#option-b-cmake-toolchain-file
.PARAMETER cmake
    Path to cmake executable.
.PARAMETER vcpkg
    Path to vcpkg executable.
#>
param (
    $Platform = 'x64-windows',
    $BuildType = 'Debug',

    $BuildDirectory = "$PSScriptRoot/build",
    $VcpkgToolchainFile = 'D:\Programs\vcpkg\scripts\buildsystems\vcpkg.cmake',

    $cmake = 'cmake',
    $vcpkg = 'vcpkg'
)

$ErrorActionPreference = 'Stop'

function log($text, $header) {
    if (-not $header) {
        $header = 'build'
    }
    Write-Host "[$header] $text" -ForegroundColor White
}

function exec($command) {
    log "$command $args" 'build exec'
    & $command $args
    if (!$?) {
        throw "[build error] $command $args = $LASTEXITCODE"
    }
}

log '=== INSTALLING DEPENDENCIES ==='
$dependencies = @('boost', 'sdl2')
$dependencies | % {
    $dependency = $_
    exec $vcpkg install "$($dependency):$Platform"
}

log '=== BUILDING MANDELBROT ==='
if (-not (Test-Path $BuildDirectory -ErrorAction Ignore)) {
    New-Item -ItemType Directory $BuildDirectory | Out-Null
}

Push-Location $BuildDirectory
try {
    exec $cmake ../ `
        "-DCMAKE_BUILD_TYPE=$BuildType" `
        "-DCMAKE_TOOLCHAIN_FILE=$VcpkgToolchainFile" `
        -G "Visual Studio 15 2017 Win64"
} finally {
    Pop-Location
}
