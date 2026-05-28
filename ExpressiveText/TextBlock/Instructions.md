## This is an Expressive Text Block implementation that can be referenced in C++ and is a lot easier to use than the one provided in the plugin.

# Implementing the Class
## Header/CPP files
For simplicity, I will be adding these classes into the ExpressiveText source code itself.
- Copy [ExpressiveTextBlock.h](ExpressiveTextBlock.h) into `..PluginFolder../Source/ExpressiveText/Public/Widgets/`
- Copy [ExpressiveTextBlock.cpp](ExpressiveTextBlock.cpp) into `..PluginFolder../Source/ExpressiveText/Private/Widgets/`
- Check for any issues and resolve them.

## [Optional] Class Icon
- Go to `..PluginFolder..Source/ExpressiveTextEditor/Public/ExpressiveTextEditor.h`
- Around Line 190, add the following two lines (Do not delete anything else)
```cpp
StyleSet->Set("ClassIcon.ExpressiveTextBlock", new IMAGE_PLUGIN_BRUSH("Core/Editor/Resources/ExTextLogo", Icon16x16));
StyleSet->Set("ClassThumbnail.ExpressiveTextBlock", new IMAGE_PLUGIN_BRUSH("Core/Editor/Resources/ExTextLogo", Icon64x64));
```

## Finally
- Compile the plugin and you're good to go!

# Usage
## Blueprint
You can drag in an Expressive Text from the Palette like any other element and begin using it. Its properties can be adjusted through functions under the Expressive Text Block category.

## C++
A pointer can be made with `UExpressiveTextBlock* MyTextBlock` and its properties can be adjusted through the functions.
