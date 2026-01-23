param (
    [string]$XmakeLuaPath = "cxx/xmake.lua"
)

if (-not (Test-Path $XmakeLuaPath)) {
    Write-Error "File not found: $XmakeLuaPath"
    exit 1
}

$content = Get-Content $XmakeLuaPath -Raw

$pattern = 'local\s+PLUGIN_NAME<[^>]*>\s*=\s*"([^"]+)"'

if ($content -match $pattern) {
    $pluginName = $matches[1]
    Write-Host "PLUGIN_NAME found:"
    Write-Host "  $pluginName"
    exit 0
} else {
    Write-Error "PLUGIN_NAME not found or pattern mismatch"
    exit 2
}
