## Install And Initial Settings.
1. Run Setup file. You need Administrator rights.
2. After installed, an icon will be displayed at 'Desktop'\ 
   ![image](https://github.com/bho3538/rdOTP/assets/12496720/4a5f39da-9c0e-4d1f-8d0c-f1c355d210ea)
3. Run 'rdOTP Settings'.\
   ![image](https://github.com/bho3538/rdOTP/assets/12496720/2c10fc58-58ae-46f7-b30a-e96ca8abbe10)
4. Click 'Install' button to register modules at system.\
   If 'Visual C++ Redistributable 2022' does not installed at your system, An error message can be displayed.\
   You can download it that link\
   Please restart program after install 'vc_redist'.\
   https://aka.ms/vs/17/release/vc_redist.x86.exe \
   https://aka.ms/vs/17/release/vc_redist.x64.exe 
6. Click 'Configuration' button to setting OTP key. If you run this program first, click 'Generate' button to generate ramdom key.
7. Click 'Show QR Code' button to create QR Code and register it at your phone.
   In this manual will use 'Microsoft Authenticator' app.\
   6-1. Download app at 'Play Store (Android)' or 'App Store (IOS)'\
   6-2. Click '+' button at right side.\
   6-3. Select 'Other'\
   6-4. An Camera app will be started. Shot QR Code at your computer.
8. Click the 'OTP Test' button to test the OTP credentials added to the mobile phone app.\
After entering the code displayed on the mobile phone app into the test window, the message box 'Test Success!' is displayed.
  * If authentication fails continuously, delete the authentication information from the mobile app and proceed to step 6 again.\ (The QR code may be taken incorrectly on your phone.)
9. Try to connect remotely using MSTSC, etc. from another device.
  If the authentication screen appears as follows, it is a success.\
  ![image](https://github.com/bho3538/rdOTP/assets/12496720/9ac0916f-dd30-4940-9cc6-4b00403c53ef)

## Troubleshooting
1. Mobile phone OTP is unavailable or the lock screen is continuously forced to shut down due to a program error in the RDP environment\
  Even with this program, you can still use your PC without OTP when you log in directly from your local computer rather than from a remote connection (RDP).\
  After you log in locally, you can add a QR code (key change) or delete a program.
2. Even in local login, the lock screen is forcibly terminated due to a program error\
  After booting the PC into safe mode, delete the file in the following path.\
  'C:\Program Files\rdOTP\rdOTPred.dll'\
After that, you can boot the PC normally, delete the program from the control panel, and send an error report.
3. If the computer's time on the OTP authentication screen is significantly different from the actual time (based on mobile phone) (more than 1 minute)\
  Due to the nature of TOTP, if time will not sync each other, can be an error\
  In this case, you can temporarily change the mobile phone time to the computer time shown on the screen and re-run the OTP app to proceed with the login date.
