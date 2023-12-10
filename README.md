# rdOTP
A Server-less time based OTP (TOTP) Autherication for Windows RDP

https://github.com/bho3538/rdOTP/assets/12496720/77d471f9-766a-4ae9-b07e-5e159950f771

## Supported OS and Requirement
Windows 8 (Server 2012) or higer version. (x86, x64)\
(ARM64 require rdOTP 1.3 or higher)\
.NET Framework 4.6.2 or higher version.\
(.NET Framework 4.8.1 required in ARM64 OS)\
Visual C++ Redistributable 2022

## Tested OS
Windows Server 2012 R2\
Wdinwos Server vNext (2024)\
Windows 10 (x86, x64)\
Windows 11 (x64, ARM64)

## How does it work?
This program register 'Credential Provider' extension at system.\
This credential provider require OTP autherication if user connect pc using RDP

## How to use this program?
[English](https://github.com/bho3538/rdOTP/blob/master/manual_en.md)\
[한국어](https://github.com/bho3538/rdOTP/blob/master/manual_ko.md)

## Todo list
Per account OTP Auth\
Another Remote Program support (if possible)

## Using OpenSource
[OTP.Net](https://github.com/kspearrin/Otp.NET)\
[QRCoder](https://github.com/codebude/QRCoder)\
Credential Provider V2 Sample From Microsoft SDK\
Lock icon by [Icons8](https://icons8.com)

## License
MIT
