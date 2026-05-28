## This document outlines how to manually update the Expressive Text plugin to recent Unreal Engine 5 versions

# Prerequisites
## Locating the Expressive Text Plugin
- If you **have Unreal Engine 5.5 installed**, you can download the Expresive Text plugin by installing it to the engine and locating the file at `UE_INSTALL_DIR/Engine/Plugins/Marketplace/(Plugin here with encrypted name)`
- If you **do not have Unreal Engine 5.5 installed**, you can either download it (deselected everything in install options for a smaller size) and obtain the plugin via the above step, or use *Asset Manager Studio* to download it directly.

## Creating a C++ Project
1) In your target Unreal Engine version (for example, 5.7) create a **C++ based project**.
2) Once done, go to the folder of said project and create a new folder named `Plugins`
3) Put the Expressive Text plugin into that Plugins folder

# Porting the Plugin
## Initial Steps
- Open up `ExpressiveText.uplugin` and remove the `EngineVersion` entry entirely.
- In the same file, remove the `Installed` entry as well.

## Porting to 5.6
- In `ExpressiveTextLayout.h` - `Line 56`
  - Change `OffsetX` to `Offset`
    
- In `ExpressiveTextCompiler.h` - `Line 107`
  - Remove the `auto` from within the parenthesis
    
- In `UnlogImplementation.h` - `Line 438` (the `ProcessFormatString` function)
  - Remove the `FString Result...` and `return...` lines only and copy the following code to replace them
  ```cpp
  TCHAR Buffer[2048];
  int32 Length = FCString::Snprintf(Buffer, UE_ARRAY_COUNT(Buffer), Format, Args...);
  if (Length >= 0 && Length < UE_ARRAY_COUNT(Buffer))
  {
      return FString(Buffer);
  }
  
  // Uh-oh
  if (Length < 0)
  {
      return FString();
  }
  
  TArray<TCHAR> LargeBuffer;
  LargeBuffer.SetNumUninitialized(Length + 1);
  FCString::Snprintf(LargeBuffer.GetData(), LargeBuffer.Num(), Format, Args...);
  return FString(LargeBuffer.GetData());
  ```
  
## Porting to 5.7
- **Apply all the changes for 5.6 before starting**
  
- `ExpressiveTextCompiler.h` - `Line 257`  
  and `ExpressiveTextRun.cpp` - `Line 133`  
  and `ExTextGoogleFontsImporterSubsystem.h` - `Line 80`  
  - Change `CompositeFont` to `GetInternalCompositeFont()`
    
- `ExTextGoogleFontsImporterSubsystem.h` - `Line 515`  
  - Change `CompositeFont` to `GetMutableInternalCompositeFont()`
    
- `ExTextGoogleFontsImporterSubsystem.h` - `Line 78`  
  - Change `CompositeFont` **on the right** to `GetInternalCompositeFont()`
  - Change `CompositeFont` **on the left** to `GetMutableInternalCompositeFont()`

## Porting to 5.8 PREVIEW
- **Apply all changes for 5.6 and 5.7 before starting**

- `UnlogImplementation.h` - `Line 288`
  and `ExpressiveTextEditorSubsystem.h` - `Line 79`
  - Change `OnPostEngineInit` to `GetOnPostEngineInit()`

- `ExTextComboBox.h` - `Line 9`
  - Change `<SSearchableComboBox.h>` to `<Widgets/Input/SSearchableComboBox.h>`

- `ExTextMultiLineEditableText.h` - `Line 23, 37, 41, 42`
  - Change `EditableTextLayout->` to `SlateEditableTextLayout.` (**Important: Arrow becomes period!**)

# Final Steps
## If you are using it in a C++ project
Technically, you are done. You can move the plugins folder into your project and your project will compile the plugin approprately.

## If you are using it in Multiple OR BP-Only projects
- Run the C++ project that you are modifying the plugin in.
- Go to the Plugins tab and find the Expressive Text plugin.
- Click on "Package" under the plugin description. (If you do not see this, make sure `Installed` is either removed or set to false in the `.uplugin` file)
- Once packaged, you can move the packaged result into 5.7's Plugins/Marketplace folder.
