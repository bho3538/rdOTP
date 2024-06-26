echo "rdOTP BUILD";
$g_currentPath = (Get-item .).FullName;
$g_msbuildPath = "C:\Program Files\Microsoft Visual Studio\2022\Community\MSBuild\Current\Bin\MSBuild.exe";
$g_innosetupPath = "C:\Program Files (x86)\Inno Setup 6\ISCC.exe";
$g_nugetPath = "C:\Users\Build\nuget.exe";

# nuget restore
& "$g_nugetPath" restore "$g_currentPath\rdOTP.sln";

# build main exe (ANY CPU)
& "$g_msbuildPath" "$g_currentPath\rdOTP.sln" -t:rdOTP -p:Configuration=Release -p:Platform="Any CPU";

## hack (ARM64 build does not create resource file. why??)
cp -Force "$g_currentPath\rdOTP\obj\Release\ko-KR" "$g_currentPath\source\rdOTP\rdOTP\obj\ARM64\Release\ko-KR"

# build main exe (arm64)
& "$g_msbuildPath" "$g_currentPath\rdOTP.sln" -t:rdOTP -p:Configuration=Release -p:Platform="ARM64";

# build service exe (ANY CPU)
& "$g_msbuildPath" "$g_currentPath\rdOTP.sln" -t:rdOTPSvc -p:Configuration=Release -p:Platform="Any CPU";

# build service exe (arm64)
& "$g_msbuildPath" "$g_currentPath\rdOTP.sln" -t:rdOTPSvc -p:Configuration=Release -p:Platform="ARM64";

# build x86 cred provider dll
& "$g_msbuildPath" "$g_currentPath\rdOTP.sln" -t:rdOTPCred -p:Configuration=Release -p:Platform="x86";

# build x64 cred provider dll
& "$g_msbuildPath" "$g_currentPath\rdOTP.sln" -t:rdOTPCred -p:Configuration=Release -p:Platform="x64";

# build arm64 cred provider dll
& "$g_msbuildPath" "$g_currentPath\rdOTP.sln" -t:rdOTPCred -p:Configuration=Release -p:Platform="ARM64";

# build x86 cred wrapper dll
& "$g_msbuildPath" "$g_currentPath\rdOTP.sln" -t:rdOTPWrap -p:Configuration=Release -p:Platform="x86";

# build x64 cred wrapper dll
& "$g_msbuildPath" "$g_currentPath\rdOTP.sln" -t:rdOTPWrap -p:Configuration=Release -p:Platform="x64";

# build arm64 cred wrapper dll
& "$g_msbuildPath" "$g_currentPath\rdOTP.sln" -t:rdOTPWrap -p:Configuration=Release -p:Platform="ARM64";

# build x86 ext exe
& "$g_msbuildPath" "$g_currentPath\rdOTP.sln" -t:rdOTPExt -p:Configuration=Release -p:Platform="x86";

# build x64 ext exe
& "$g_msbuildPath" "$g_currentPath\rdOTP.sln" -t:rdOTPExt -p:Configuration=Release -p:Platform="x64";

# build arm64 ext exe
& "$g_msbuildPath" "$g_currentPath\rdOTP.sln" -t:rdOTPExt -p:Configuration=Release -p:Platform="ARM64";

# codesign (currently no certificate --> skip)

# create setup file (using inno setup)
& "$g_innosetupPath" "$g_currentPath\setup\rdOTPSetup.iss";

# backup pdb files
New-Item -ItemType Directory -Force "$g_currentPath\setup\PDB";
New-Item -ItemType Directory -Force "$g_currentPath\setup\PDB\ARM64";
New-Item -ItemType Directory -Force "$g_currentPath\setup\PDB\x86";
New-Item -ItemType Directory -Force "$g_currentPath\setup\PDB\x64";

cp -Force "$g_currentPath\rdOTP\bin\Release\rdOTP.pdb" "$g_currentPath\setup\PDB";
cp -Force "$g_currentPath\rdOTP\bin\ARM64\Release\rdOTP.pdb" "$g_currentPath\setup\PDB\ARM64";

cp -Force "$g_currentPath\rdOTPSvc\bin\Release\rdOTP.pdb" "$g_currentPath\setup\PDB";
cp -Force "$g_currentPath\rdOTPSvc\bin\ARM64\Release\rdOTP.pdb" "$g_currentPath\setup\PDB\ARM64";

cp -Force "$g_currentPath\Release\rdOTPCred.pdb" "$g_currentPath\setup\PDB\x86";
cp -Force "$g_currentPath\Release\rdOTPWrap.pdb" "$g_currentPath\setup\PDB\x86";
cp -Force "$g_currentPath\Release\rdOTPExt.pdb" "$g_currentPath\setup\PDB\x86";

cp -Force "$g_currentPath\x64\Release\rdOTPCred.pdb" "$g_currentPath\setup\PDB\x64";
cp -Force "$g_currentPath\x64\Release\rdOTPWrap.pdb" "$g_currentPath\setup\PDB\x64";
cp -Force "$g_currentPath\x64\Release\rdOTPExt.pdb" "$g_currentPath\setup\PDB\x64";

cp -Force "$g_currentPath\ARM64\Release\rdOTPCred.pdb" "$g_currentPath\setup\PDB\ARM64";
cp -Force "$g_currentPath\ARM64\Release\rdOTPWrap.pdb" "$g_currentPath\setup\PDB\ARM64";
cp -Force "$g_currentPath\ARM64\Release\rdOTPExt.pdb" "$g_currentPath\setup\PDB\ARM64";