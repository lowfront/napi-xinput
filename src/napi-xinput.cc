#include <windows.h>
#pragma comment(lib, "Xinput.lib")
#include <Xinput.h>
#include <napi.h>

DWORD dwResult;

Napi::Object GetState(const Napi::CallbackInfo& info)
{
  Napi::Env env = info.Env();
  Napi::Object result = Napi::Object::New(env);

  if (info.Length() < 1) {
    Napi::TypeError::New(env, "Wrong number of arguments").ThrowAsJavaScriptException();
    return result;
  }
  int i = info[0].ToNumber().Int32Value();
  XINPUT_STATE state;
  ZeroMemory(&state, sizeof(XINPUT_STATE));
  dwResult = XInputGetState(i, &state);

  if (dwResult == ERROR_SUCCESS)
  {
    result.Set("dwPacketNumber", state.dwPacketNumber);
    result.Set("Gamepad.wButtons", state.Gamepad.wButtons);
    result.Set("Gamepad.bLeftTrigger", state.Gamepad.bLeftTrigger);
    result.Set("Gamepad.bRightTrigger", state.Gamepad.bRightTrigger);
    result.Set("Gamepad.sThumbLX", state.Gamepad.sThumbLX);
    result.Set("Gamepad.sThumbLY", state.Gamepad.sThumbLY);
    result.Set("Gamepad.sThumbRX", state.Gamepad.sThumbRX);
    result.Set("Gamepad.sThumbRY", state.Gamepad.sThumbRY);
    return result;
  }
  else 
  {
    return result;
  }
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
  
  result.Set("BatteryType", pBatteryInformation.BatteryType);
  result.Set("BatteryLevel", pBatteryInformation.BatteryLevel);

  return result;
}

Napi::Object GetCapabilities(const Napi::CallbackInfo& info)
{
  Napi::Env env = info.Env();
  Napi::Object result = Napi::Object::New(env);

  if (info.Length() < 1) {
    Napi::TypeError::New(env, "Wrong number of arguments").ThrowAsJavaScriptException();
    return result;
  }
  int i = info[0].ToNumber().Int32Value();

  XINPUT_CAPABILITIES pCapabilities;
  ZeroMemory(&pCapabilities, sizeof(XINPUT_CAPABILITIES));

  XInputGetCapabilities(i, XINPUT_FLAG_GAMEPAD, &pCapabilities);

  result.Set("Type", pCapabilities.Type);
  result.Set("SubType", pCapabilities.SubType);
  result.Set("Flags", pCapabilities.Flags);
  result.Set("Gamepad.wButtons", uint16_t(pCapabilities.Gamepad.wButtons));
  result.Set("Gamepad.bLeftTrigger", pCapabilities.Gamepad.bLeftTrigger);
  result.Set("Gamepad.bRightTrigger", pCapabilities.Gamepad.bRightTrigger);
  result.Set("Gamepad.sThumbLX", uint16_t(pCapabilities.Gamepad.sThumbLX));
  result.Set("Gamepad.sThumbLY", uint16_t(pCapabilities.Gamepad.sThumbLY));
  result.Set("Gamepad.sThumbRX", uint16_t(pCapabilities.Gamepad.sThumbRX));
  result.Set("Gamepad.sThumbRY", uint16_t(pCapabilities.Gamepad.sThumbRY));
  result.Set("Vibration.wLeftMotorSpeed", pCapabilities.Vibration.wLeftMotorSpeed);
  result.Set("Vibration.wRightMotorSpeed", pCapabilities.Vibration.wRightMotorSpeed);

  return result;
}

Napi::Object GetKeystroke(const Napi::CallbackInfo& info)
{
  Napi::Env env = info.Env();
  Napi::Object result = Napi::Object::New(env);

  if (info.Length() < 1) {
    Napi::TypeError::New(env, "Wrong number of arguments").ThrowAsJavaScriptException();
    return result;
  }
  int i = info[0].ToNumber().Int32Value();

  PXINPUT_KEYSTROKE pKeystroke;
  ZeroMemory(pKeystroke, sizeof(PXINPUT_KEYSTROKE));

  XInputGetKeystroke(i, 0, pKeystroke);
  result.Set("VirtualKey", uint16_t(pKeystroke->VirtualKey));
  result.Set("Unicode", pKeystroke->Unicode);
  result.Set("Flags", pKeystroke->Flags);
  result.Set("UserIndex", pKeystroke->UserIndex);
  result.Set("HidCode", pKeystroke->HidCode);
  
  return result;
}

// Napi::Object GetCapabilitiesEx(const Napi::CallbackInfo& info)
// {
//   Napi::Env env = info.Env();
//   Napi::Object result = Napi::Object::New(env);

//   struct XINPUT_CAPABILITIES_EX
//   {
//       XINPUT_CAPABILITIES Capabilities;
//       WORD vendorId;
//       WORD productId;
//       WORD revisionId;
//       DWORD a4;
//   };

//   typedef DWORD(_stdcall* _XInputGetCapabilitiesEx)(DWORD a1, DWORD dwUserIndex, DWORD dwFlags, XINPUT_CAPABILITIES_EX* pCapabilities);
//   _XInputGetCapabilitiesEx XInputGetCapabilitiesEx;

//   HMODULE moduleHandle = LoadLibrary(TEXT("XInput1_4.dll"));
//   XInputGetCapabilitiesEx = (_XInputGetCapabilitiesEx)GetProcAddress(moduleHandle, (char*)108);
  
//   if (info.Length() < 1) {
//     Napi::TypeError::New(env, "Wrong number of arguments").ThrowAsJavaScriptException();
//     return result;
//   }

//   int i = info[0].ToNumber().Int32Value();

//   XINPUT_CAPABILITIES_EX capsEx;
//   XInputGetCapabilitiesEx(1, i, 0, &capsEx);

//   result.Set("vendorId", capsEx.vendorId);
//   result.Set("productId", capsEx.productId);
//   result.Set("revisionId", capsEx.revisionId);
//   result.Set("a4", capsEx.a4);

//   return result;
// }

Napi::Object Init(Napi::Env env, Napi::Object exports)
{
  exports.Set(Napi::String::New(env, "GetState"), Napi::Function::New(env, GetState));
  exports.Set(Napi::String::New(env, "SetState"), Napi::Function::New(env, SetState));
  exports.Set(Napi::String::New(env, "GetBatteryInformation"), Napi::Function::New(env, GetBatteryInformation));
  exports.Set(Napi::String::New(env, "GetCapabilities"), Napi::Function::New(env, GetCapabilities));
  exports.Set(Napi::String::New(env, "GetKeystroke"), Napi::Function::New(env, GetKeystroke));
  return exports;
}

NODE_API_MODULE(addon, Init);
