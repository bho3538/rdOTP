;==============================================================================================================
; *** Version History ***
;**************************************************************************************************************

[Setup]
PrivilegesRequired=admin
OutputBaseFilename=rdOTP 1.0
AppName=rdOTP
AppVersion=1.0
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
ArchitecturesInstallIn64BitMode=x64
LanguageDetectionMethod=uilanguage
ShowLanguageDialog=yes
VersionInfoProductVersion=2.0
VersionInfoVersion=2.0
UsePreviousTasks=no


[Languages]
Name: "ENU" ; MessagesFile: "compiler:Default.isl"
;Name: "KOR" ; MessagesFile: "compiler:Languages\Korean.isl";

[Dirs]

[Files]

Source: ".\Source\rdOTP\Otp.NET.dll"; DestDir: "{app}"; Flags: restartreplace uninsrestartdelete ignoreversion
Source: ".\Source\rdOTP\QRCoder.dll"; DestDir: "{app}"; Flags: restartreplace uninsrestartdelete ignoreversion
Source: ".\Source\rdOTP\rdOTP.exe"; DestDir: "{app}"; Flags: restartreplace uninsrestartdelete ignoreversion
Source: ".\Source\rdOTP\x86\rdOTPCred.dll"; DestDir: "{app}"; Flags: 32bit restartreplace uninsrestartdelete ignoreversion; Check: not Is64BitInstallMode
Source: ".\Source\rdOTP\x86\rdOTPWrap.dll"; DestDir: "{app}"; Flags: 32bit restartreplace uninsrestartdelete ignoreversion; Check: not Is64BitInstallMode
Source: ".\Source\rdOTP\x64\rdOTPCred.dll"; DestDir: "{app}"; Flags: 64bit restartreplace uninsrestartdelete ignoreversion; Check: Is64BitInstallMode
Source: ".\Source\rdOTP\x64\rdOTPWrap.dll"; DestDir: "{app}"; Flags: 64bit restartreplace uninsrestartdelete ignoreversion; Check: Is64BitInstallMode


[Icons]
Name: "{group}\rdOTP Settings"; Filename: "{app}\rdOTP.exe"
Name: "{group}\Uninstall rdOTP"; Filename: "{uninstallexe}"
Name: "{userdesktop}\rdOTP Settings"; Filename: "{app}\rdOTP.exe"; Tasks: desktopicon

[Registry]
;Root: HKLM; Subkey: "Software\rdOTP"; ValueName: "*"; Flags : deletevalue;

[Run]

[UninstallRun]
Filename: "{sys}\regsvr32.exe"; Parameters: "/u /s rdOTPCred.dll"; WorkingDir: "{app}"; Flags: runhidden;

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





