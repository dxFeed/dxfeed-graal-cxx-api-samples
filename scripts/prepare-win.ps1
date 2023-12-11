<#
    .SYNOPSIS
        This script prepares example projects..
    .PARAMETER DxFeedGraalCxxApiVersion
        The dxFeed Graal CXX API version (https://github.com/dxFeed/dxfeed-graal-cxx-api).
    .PARAMETER PathToDownload
        The path for downloading artifacts.
 #>
#>
param (
    [Parameter(Mandatory = $true)]
    [string] $DxFeedGraalCxxApiVersion,
    [string] $PathToDownload = "$PSScriptRoot/downloads"
)

if (!$DxFeedGraalCxxApiVersion)
{
    Write-Error "\`$DxFeedGraalCxxApiVersion is not set"
}
else
{
    Get-ChildItem "$PathToDownload" -Exclude ".gitkeep" | Remove-Item -Recurse -Force -Confirm:$false
    New-Item -ItemType Directory -Force -Path "$PathToDownload" -ErrorAction SilentlyContinue | Out-Null
    $DxFeedGraalCxxApiUri = "https://github.com/dxFeed/dxfeed-graal-cxx-api"
    $DxFeedGraalCxxApiArtifactUri = "$DxFeedGraalCxxApiUri/releases/download/$DxFeedGraalCxxApiVersion/dxFeedGraalCxxApi-$DxFeedGraalCxxApiVersion-x86_64-windows-Release.zip"
    $DxFeedGraalCxxApiArtifactPath = "$PathToDownload/dxFeedGraalCxxApi-$DxFeedGraalCxxApiVersion-x86_64-windows-Release.zip"
    $DxFeedGraalCxxApiFolderPath = "$PathToDownload/dxFeedGraalCxxApi-$DxFeedGraalCxxApiVersion-x86_64-windows-Release"

    Write-Host "URI: '$DxFeedGraalCxxApiArtifactUri'"
    Write-Host "PATH: '$DxFeedGraalCxxApiArtifactPath'"
    Invoke-WebRequest "$DxFeedGraalCxxApiArtifactUri" -OutFile "$DxFeedGraalCxxApiArtifactPath"
    Expand-Archive "$DxFeedGraalCxxApiArtifactPath" -DestinationPath "$PathToDownload" -Force


    $VsProjectSamplePath = "$PSScriptRoot/../vs-project-sample"
    $VsProjectSampleThirdPartyPath = "$VsProjectSamplePath/third_party/dxfeed-graal-cxx-api"
    Get-ChildItem "$VsProjectSampleThirdPartyPath" -Exclude ".gitkeep" | Remove-Item -Recurse -Force -Confirm:$false
    Copy-Item -Path "$DxFeedGraalCxxApiFolderPath/*" -Destination "$VsProjectSampleThirdPartyPath" -Recurse -Force -Confirm:$false
    Get-ChildItem "$VsProjectSampleThirdPartyPath"

    $VsProjectSampleReadmePath = "$VsProjectSamplePath/README.md"
    (Get-Content $VsProjectSampleReadmePath -raw) -replace "$DxFeedGraalCxxApiUri/releases/tag/(v\d+\.\d+\.\d+[^)]*)", "$DxFeedGraalCxxApiArtifactUri" |
            Set-Content $VsProjectSampleReadmePath
    (Get-Content $VsProjectSampleReadmePath -raw) -replace "$DxFeedGraalCxxApiUri/releases/tag/(v\d+\.\d+\.\d+[^)]*)", "$DxFeedGraalCxxApiArtifactUri" |
            Set-Content $VsProjectSampleReadmePath

    Get-Content $VsProjectSampleReadmePath -raw
}
