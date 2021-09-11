#include <windows.h>
#pragma comment(lib, "Xinput.lib")
#include <Xinput.h>
#include <napi.h>

#include <chrono>
#include <thread>

DWORD dwResult;

std::thread t1([] {
    while (1) {}
});

Napi::Boolean GetState(const Napi::CallbackInfo& info)
{
  Napi::Env env = info.Env();

  if (info.Length() < 1) {
    Napi::TypeError::New(env, "Wrong number of arguments").ThrowAsJavaScriptException();
    return Napi::Boolean::New(env, false);
  }
  int i = info[0].ToNumber().Int32Value();
  XINPUT_STATE state;
  ZeroMemory(&state, sizeof(XINPUT_STATE));
  dwResult = XInputGetState(i, &state);

  return Napi::Boolean::New(env, dwResult == ERROR_SUCCESS);
}
Napi::Boolean SetState(const Napi::CallbackInfo& info)
{
  Napi::Env env = info.Env();
  
  if (info.Length() < 3) {
    Napi::TypeError::New(env, "Wrong number of arguments").ThrowAsJavaScriptException();
    // return Napi::Number::New(env, 0);
    return Napi::Boolean::New(env, false);
  }

  int i = info[0].ToNumber().Int32Value();
  float left = info[1].ToNumber();
  float right = info[2].ToNumber();

  XINPUT_VIBRATION vibration;
  ZeroMemory(&vibration, sizeof(XINPUT_VIBRATION));
  vibration.wLeftMotorSpeed = static_cast<WORD>(left*65535); // use any value between 0-65535 here
  vibration.wRightMotorSpeed = static_cast<WORD>(right*65535); // use any value between 0-65535 here
  dwResult = XInputSetState(i, &vibration);

  // return Napi::Number::New(env, static_cast<WORD>(left*65535));

  return Napi::Boolean::New(env, dwResult == ERROR_SUCCESS);
}

Napi::Object GetBatteryInformation(const Napi::CallbackInfo& info)
{
  Napi::Env env = info.Env();
  Napi::Object result = Napi::Object::New(env);

  if (info.Length() < 2) {
    Napi::TypeError::New(env, "Wrong number of arguments").ThrowAsJavaScriptException();
    return result;
  }

  XINPUT_BATTERY_INFORMATION pBatteryInformation;
  ZeroMemory(&pBatteryInformation, sizeof(XINPUT_BATTERY_INFORMATION));
  
  int i = info[0].ToNumber().Int32Value();
  int type = info[0].ToNumber().Int32Value(); // 0 - BATTERY_DEVTYPE_GAMEPAD, 1 - BATTERY_DEVTYPE_HEADSET
  
  XInputGetBatteryInformation(i, type, &pBatteryInformation);

  result.Set("type", pBatteryInformation.BatteryType);
  result.Set("level", pBatteryInformation.BatteryLevel);

  return result;
}

Napi::Object Init(Napi::Env env, Napi::Object exports)
{
  exports.Set(Napi::String::New(env, "GetState"), Napi::Function::New(env, GetState));
  exports.Set(Napi::String::New(env, "SetState"), Napi::Function::New(env, SetState));
  exports.Set(Napi::String::New(env, "GetBatteryInformation"), Napi::Function::New(env, GetBatteryInformation));
  return exports;
}

NODE_API_MODULE(addon, Init);
