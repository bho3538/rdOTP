;==============================================================================================================
; *** Version History ***
;**************************************************************************************************************

[Setup]
PrivilegesRequired=admin
OutputBaseFilename=rdOTP 1.8.0.0
AppName=rdOTP
AppVersion=1.8.0.0
AppVerName=rdOTP
AppPublisher=bho3538
AppPublisherURL=https://github.com/bho3538/rdOTP
UsePreviousAppDir=yes
DirExistsWarning=no
DefaultDirName={pf}\rdOTP
DefaultGroupName=rdOTP
UninstallDisplayIcon={app}\rdOTP.exe
UninstallDisplayName=rdOTP Remove
DisableStartupPrompt=yes
DisableWelcomePage=no
DisableReadyMemo=no
DisableReadyPage=no
DisableDirPage=yes
DisableProgramGroupPage=no
DisableFinishedPage=no
Compression=lzma
SolidCompression=yes
WizardImageStretch=no
UninstallFilesDir={pf}\rdOTP\unRDOTP
UninstallLogMode=append
ArchitecturesInstallIn64BitMode=x64 arm64
LanguageDetectionMethod=uilanguage
ShowLanguageDialog=yes
VersionInfoProductVersion=1.8.0.0
VersionInfoVersion=1.8.0.0
UsePreviousTasks=no


[Languages]
Name: "ENU" ; MessagesFile: "compiler:Default.isl"
;Name: "KOR" ; MessagesFile: "compiler:Languages\Korean.isl";

[Dirs]

[Files]
Source: "..\rdOTP\bin\Release\Otp.NET.dll"; DestDir: "{app}"; Flags: restartreplace uninsrestartdelete ignoreversion
Source: "..\rdOTP\bin\Release\QRCoder.dll"; DestDir: "{app}"; Flags: restartreplace uninsrestartdelete ignoreversion 
Source: "..\rdOTP\bin\Release\ko-KR\rdOTP.resources.dll"; DestDir: "{app}\ko-KR"; Flags: restartreplace uninsrestartdelete ignoreversion;
Source: "..\rdOTP\bin\Release\rdOTP.exe"; DestDir: "{app}"; Flags: restartreplace uninsrestartdelete ignoreversion; Check: not InstallARM64
Source: "..\rdOTPSvc\bin\Release\rdOTPSvc.exe"; DestDir: "{app}"; Flags: restartreplace uninsrestartdelete ignoreversion; Check: not InstallARM64
Source: "..\rdOTP\bin\ARM64\Release\rdOTP.exe"; DestDir: "{app}"; Flags: restartreplace uninsrestartdelete ignoreversion; Check: InstallARM64
Source: "..\rdOTPSvc\bin\ARM64\Release\rdOTPSvc.exe"; DestDir: "{app}"; Flags: restartreplace uninsrestartdelete ignoreversion; Check: InstallARM64

Source: "..\Release\rdOTPCred.dll"; DestDir: "{app}"; Flags: 32bit restartreplace uninsrestartdelete ignoreversion; Check: InstallOtherArch
Source: "..\Release\rdOTPWrap.dll"; DestDir: "{app}"; Flags: 32bit restartreplace uninsrestartdelete ignoreversion; Check: InstallOtherArch
Source: "..\Release\rdOTPExt.exe"; DestDir: "{app}"; Flags: 32bit restartreplace uninsrestartdelete ignoreversion; Check: InstallOtherArch

Source: "..\x64\Release\rdOTPCred.dll"; DestDir: "{app}"; Flags: 64bit restartreplace uninsrestartdelete ignoreversion; Check: InstallX64
Source: "..\x64\Release\rdOTPWrap.dll"; DestDir: "{app}"; Flags: 64bit restartreplace uninsrestartdelete ignoreversion; Check: InstallX64
Source: "..\x64\Release\rdOTPExt.exe"; DestDir: "{app}"; Flags: 64bit restartreplace uninsrestartdelete ignoreversion; Check: InstallX64

Source: "..\ARM64\Release\rdOTPCred.dll"; DestDir: "{app}"; Flags: 64bit restartreplace uninsrestartdelete ignoreversion; Check: InstallARM64
Source: "..\ARM64\Release\rdOTPWrap.dll"; DestDir: "{app}"; Flags: 64bit restartreplace uninsrestartdelete ignoreversion; Check: InstallARM64
Source: "..\ARM64\Release\rdOTPExt.exe"; DestDir: "{app}"; Flags: 64bit restartreplace uninsrestartdelete ignoreversion; Check: InstallARM64


[Icons]
Name: "{group}\rdOTP Settings"; Filename: "{app}\rdOTP.exe"
Name: "{group}\Uninstall rdOTP"; Filename: "{uninstallexe}"
Name: "{userdesktop}\rdOTP Settings"; Filename: "{app}\rdOTP.exe"; Tasks: desktopicon

[Registry]
;Root: HKLM; Subkey: "Software\rdOTP"; ValueName: "*"; Flags : deletevalue;

[Run]

[UninstallRun]
Filename: "{sys}\regsvr32.exe"; Parameters: "/u /s rdOTPCred.dll"; WorkingDir: "{app}"; Flags: runhidden;
Filename: "{sys}\sc.exe"; Parameters: "stop rdOTPSvc"; RunOnceId: "Stop rdOTP Service"; Flags: runhidden waituntilterminated
Filename: "{sys}\sc.exe"; Parameters: "delete rdOTPSvc"; RunOnceId: "Remove rdOTP Service"; Flags: runhidden waituntilterminated


[Tasks]
Name: "desktopicon"; Description: "{cm:CreateDesktopIcon}"; GroupDescription: "{cm:AdditionalIcons}";
Name: "quicklaunchicon"; Description: "{cm:CreateQuickLaunchIcon}"; GroupDescription: "{cm:AdditionalIcons}"; OnlyBelowVersion: 6.1; Check: not IsAdminInstallMode


[Code]
procedure CurUninstallStepChanged(CurUninstallStep: TUninstallStep);
begin
  if CurUninstallStep = usPostUninstall then
  begin
    if RegKeyExists(HKEY_LOCAL_MACHINE, 'SOFTWARE\rdOTP') then
      if MsgBox('Do you want to delete Secret key?If you update this program, select NO',
        mbConfirmation, MB_YESNO) = IDYES
      then
        RegDeleteKeyIncludingSubkeys(HKEY_LOCAL_MACHINE, 'SOFTWARE\rdOTP');
  end;
end;

function InstallX64: Boolean;
begin
  Result := Is64BitInstallMode and (ProcessorArchitecture = paX64);
end;

function InstallARM64: Boolean;
begin
  Result := Is64BitInstallMode and (ProcessorArchitecture = paARM64);
end;

function InstallOtherArch: Boolean;
begin
  Result := not InstallX64 and not InstallARM64;
end;





