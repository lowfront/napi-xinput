export namespace xinput {
  function GetState(userIndex: number): {
    dwPacketNumber: number;
    'Gamepad.wButtons': number;
    'Gamepad.bLeftTrigger': number;
    'Gamepad.bRightTrigger': number;
    'Gamepad.sThumbLX': number;
    'Gamepad.sThumbLY': number;
    'Gamepad.sThumbRX': number;
    'Gamepad.sThumbRY': number;
  }

  function SetState(userIndex: number, leftMotorSpeed: number, rightMotorSpeed: number): boolean

  function GetBatteryInformation(userIndex: number): {
    BatteryType: number;
    BatteryLevel: number;
  }

  function GetCapabilities(userIndex: number): {
    Type: number;
    SubType: number;
    Flags: number;
    'Gamepad.wButtons': number;
    'Gamepad.bLeftTrigger': number;
    'Gamepad.bRightTrigger': number;
    'Gamepad.sThumbLX': number;
    'Gamepad.sThumbLY': number;
    'Gamepad.sThumbRX': number;
    'Gamepad.sThumbRY': number;
    'Vibration.wLeftMotorSpeed': number;
    'Vibration.wRightMotorSpeed': number;
  }
  function GetKeystroke(userIndex: number): {
    VirtualKey: number;
    Unicode: number;
    Flags: number;
    UserIndex: number;
    HidCode: number;
  }
};

export namespace constants {
  const XINPUT_DEVSUBTYPE_UNKNOWN = 0x00;
  const XINPUT_DEVSUBTYPE_WHEEL = 0x02;
  const XINPUT_DEVSUBTYPE_ARCADE_STICK = 0x03;
  const XINPUT_DEVSUBTYPE_FLIGHT_STICK = 0x04;
  const XINPUT_DEVSUBTYPE_DANCE_PAD = 0x05;
  const XINPUT_DEVSUBTYPE_GUITAR = 0x06;
  const XINPUT_DEVSUBTYPE_GUITAR_ALTERNATE = 0x07;
  const XINPUT_DEVSUBTYPE_DRUM_KIT = 0x08;
  const XINPUT_DEVSUBTYPE_GUITAR_BASS = 0x0B;
  const XINPUT_DEVSUBTYPE_ARCADE_PAD = 0x13;
  const XINPUT_CAPS_VOICE_SUPPORTED = 0x0004;
  const XINPUT_CAPS_FFB_SUPPORTED = 0x0001;
  const XINPUT_CAPS_WIRELESS = 0x0002;
  const XINPUT_CAPS_PMD_SUPPORTED = 0x0008;
  const XINPUT_CAPS_NO_NAVIGATION = 0x0010;
  const XINPUT_GAMEPAD_DPAD_UP = 0x0001;
  const XINPUT_GAMEPAD_DPAD_DOWN = 0x0002;
  const XINPUT_GAMEPAD_DPAD_LEFT = 0x0004;
  const XINPUT_GAMEPAD_DPAD_RIGHT = 0x0008;
  const XINPUT_GAMEPAD_START = 0x0010;
  const XINPUT_GAMEPAD_BACK = 0x0020;
  const XINPUT_GAMEPAD_LEFT_THUMB = 0x0040;
  const XINPUT_GAMEPAD_RIGHT_THUMB = 0x0080;
  const XINPUT_GAMEPAD_LEFT_SHOULDER = 0x0100;
  const XINPUT_GAMEPAD_RIGHT_SHOULDER = 0x0200;
  const XINPUT_GAMEPAD_A = 0x1000;
  const XINPUT_GAMEPAD_B = 0x2000;
  const XINPUT_GAMEPAD_X = 0x4000;
  const XINPUT_GAMEPAD_Y = 0x8000;
  const XINPUT_GAMEPAD_LEFT_THUMB_DEADZONE = 7849;
  const XINPUT_GAMEPAD_RIGHT_THUMB_DEADZONE = 8689;
  const XINPUT_GAMEPAD_TRIGGER_THRESHOLD = 30;
  const XINPUT_FLAG_GAMEPAD = 0x00000001;
  const BATTERY_DEVTYPE_GAMEPAD = 0x00;
  const BATTERY_DEVTYPE_HEADSET = 0x01;
  const BATTERY_TYPE_DISCONNECTED = 0x00;
  const BATTERY_TYPE_WIRED = 0x01;
  const BATTERY_TYPE_ALKALINE = 0x02;
  const BATTERY_TYPE_NIMH = 0x03;
  const BATTERY_TYPE_UNKNOWN = 0xFF;
  const BATTERY_LEVEL_EMPTY = 0x00;
  const BATTERY_LEVEL_LOW = 0x01;
  const BATTERY_LEVEL_MEDIUM = 0x02;
  const BATTERY_LEVEL_FULL = 0x03;
  const XUSER_MAX_COUNT = 4;
  const XUSER_INDEX_ANY = 0x000000FF;
  const VK_PAD_A = 0x5800;
  const VK_PAD_B = 0x5801;
  const VK_PAD_X = 0x5802;
  const VK_PAD_Y = 0x5803;
  const VK_PAD_RSHOULDER = 0x5804;
  const VK_PAD_LSHOULDER = 0x5805;
  const VK_PAD_LTRIGGER = 0x5806;
  const VK_PAD_RTRIGGER = 0x5807;
  const VK_PAD_DPAD_UP = 0x5810;
  const VK_PAD_DPAD_DOWN = 0x5811;
  const VK_PAD_DPAD_LEFT = 0x5812;
  const VK_PAD_DPAD_RIGHT = 0x5813;
  const VK_PAD_START = 0x5814;
  const VK_PAD_BACK = 0x5815;
  const VK_PAD_LTHUMB_PRESS = 0x5816;
  const VK_PAD_RTHUMB_PRESS = 0x5817;
  const VK_PAD_LTHUMB_UP = 0x5820;
  const VK_PAD_LTHUMB_DOWN = 0x5821;
  const VK_PAD_LTHUMB_RIGHT = 0x5822;
  const VK_PAD_LTHUMB_LEFT = 0x5823;
  const VK_PAD_LTHUMB_UPLEFT = 0x5824;
  const VK_PAD_LTHUMB_UPRIGHT = 0x5825;
  const VK_PAD_LTHUMB_DOWNRIGHT = 0x5826;
  const VK_PAD_LTHUMB_DOWNLEFT = 0x5827;
  const VK_PAD_RTHUMB_UP = 0x5830;
  const VK_PAD_RTHUMB_DOWN = 0x5831;
  const VK_PAD_RTHUMB_RIGHT = 0x5832;
  const VK_PAD_RTHUMB_LEFT = 0x5833;
  const VK_PAD_RTHUMB_UPLEFT = 0x5834;
  const VK_PAD_RTHUMB_UPRIGHT = 0x5835;
  const VK_PAD_RTHUMB_DOWNRIGHT = 0x5836;
  const VK_PAD_RTHUMB_DOWNLEFT = 0x5837;
  const XINPUT_KEYSTROKE_KEYDOWN = 0x0001;
  const XINPUT_KEYSTROKE_KEYUP = 0x0002;
  const XINPUT_KEYSTROKE_REPEAT = 0x0004;
};