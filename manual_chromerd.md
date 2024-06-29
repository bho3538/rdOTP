## Setting chrome remote desktop (beta)
Enable OTP Authentication when access using Chrome Remote Desktop.

### Requirememts
rdOTP 1.8.0.0 + \
Configure basic rdOTP setting.

### How to
1. Run rdOTP and click 'Advanced Configuration'.\
   ![main](https://github.com/bho3538/rdOTP/assets/12496720/1da24b8c-57a5-42ee-9183-205fc46fc8f3)
2. Select 'Enable OTP at Chrome Remote Desktop' and Click 'Install' and 'Start' service\
   ![adv_setting](https://github.com/bho3538/rdOTP/assets/12496720/ad8cdd60-3fb3-4f43-8981-51216a5745a7)\
   You only need to this once the first time.\
   When installing the service, 'rdOTPSvc' is installed on the system and configured to run automatically when booting.
3. Click 'Screen Lock Test' and check computer has been locked.
4. Access computer using 'Chrome Remote Desktop' and check OTP authentication screen has been displayed.
