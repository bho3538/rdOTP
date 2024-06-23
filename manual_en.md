## Install And Initial Settings.
1. Run Setup file. You need Administrator rights.\
2. After installed, an icon will be displayed at 'Desktop'\
   ![image](https://github.com/bho3538/rdOTP/assets/12496720/4a5f39da-9c0e-4d1f-8d0c-f1c355d210ea)\
   If 'Visual C++ Redistributable 2022' does not installed at your system, An error message can be displayed.\
   ![image](https://github.com/bho3538/rdOTP/assets/12496720/646088e5-a70c-463c-90cf-ab9c3da54376)\
   Click 'Download' button (recommend) or access that link manually\
   Please restart program after install 'vc_redist'.\
   x86 : https://aka.ms/vs/17/release/vc_redist.x86.exe \
   x64 : https://aka.ms/vs/17/release/vc_redist.x64.exe \
   ARM64 : https://aka.ms/vs/17/release/vc_redist.ARM64.exe\
4. Run 'rdOTP Settings'.\
   ![image](https://github.com/bho3538/rdOTP/assets/12496720/f1152f72-2f13-4ec4-879c-c46a6c1e1ed5)
5. Click 'Install' button to register modules at system.\

6. Click 'Configuration' button to setting OTP key. If you run this program first, click 'Generate' button to generate ramdom key.
   ![image](https://github.com/bho3538/rdOTP/assets/12496720/170b4d17-1b1c-4e38-90c3-17a143aace06)
7. Click 'Show QR Code' button to create QR Code and register it at your phone.
   In this manual will use 'Microsoft Authenticator' app.\
   6-1. Download app at 'Play Store (Android)' or 'App Store (IOS)'\
   6-2. Click '+' button at right side.\
   6-3. Select 'Other'\
   6-4. An Camera app will be started. Shot QR Code at your computer.
8. Click the 'OTP Test' button to test the OTP credentials added to the mobile phone app.\
After entering the code displayed on the mobile phone app into the test window, the message box 'Test Success!' is displayed.
  * If authentication fails continuously, delete the authentication information from the mobile app and proceed to step 6 again.\ (The QR code may be taken incorrectly on your phone.)
8. Try to connect remotely using MSTSC, etc. from another device.
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
