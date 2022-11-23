# odin_whitebox
example on how to make odin work with whitebox.

*Please Note: This process is currently very cumbersome to set up and use and does not take advantage of WhiteBox's actual capability (by a long shot).  This is presented as one working example in case you want to inspect the inputs/outputs of some of your Odin procs.*

## Overview:   
[Odin Language Home Page](https://odin-lang.org/)   
[Whitebox](https://whitebox.systems/)   


## Instructions:  
1. Follow instructions to get/compile Odin and install WhiteBox
    - The [Odin](https://discord.com/invite/sVBPHEv) and [WhiteBox](https://t.co/Oky8t1Ao7O) Discord servers are very helpful
    - Specifically, thanks @4984 and @azmr, since you guys did most of the work helping me out!
1. Install the WhiteBox plugin in your editor of choice
    - I use VS Code
1. Compile `add.odin` to .dll by running `build.bat`
1. Open `whitebox_hack.c` in your editor
1. Start the WhiteBox executable
    - NOTE: WhiteBox MUST be running _before_ trying to connect.
1. Start the WhiteBox plugin
    - In VS Code, press `CTRL + SHIFT + P` and select `WhiteBox: Connect`
1. In WhiteBox, create a new profile to point to the `odin_add.dll`
    - Preferences
    - `clone`
    - Set a name
        - I named mine `dll`
    - Click the `DLL files` tab
    - Scroll down and click `Add group` button
    - In the text box, enter the path to your `odin_add.dll`
    - click `OK` to save
![image](https://user-images.githubusercontent.com/3990931/203457781-12983be6-9796-4253-a0c0-d48f234c4dcf.png)
1. Click on a line of source code and Watch The Magic!
![image](https://user-images.githubusercontent.com/3990931/203457930-3d7ca6c0-23a7-4a0f-8124-df896cbdb835.png)

## How does this work?  

Currently, WhiteBox is unable to work with Odin source code. However, after a fun screen-sharing session with Andrew (@azmr, creator of WhiteBox), we managed to get WhiteBox to communicate with an Odin .dll.

Refer to the [Odin Binding to C docs](https://odin-lang.org/news/binding-to-c/) and the discussion on [Implicit context system](https://odin-lang.org/docs/overview/#implicit-context-system).  

Basically, we create a global context and set it in the `main` to the actual context.  Then inside the proc we want to view in WhiteBox, we can get the global context and ensure the correct symbols are created in the .dll.  

```
package main
import "core:fmt"
import "core:runtime"

g_context : runtime.Context 

main :: proc() {
    g_context = context
    x:=add(1.0,1.0)
    fmt.println("Hello Whitebox!")
    fmt.println(x)
}

@(export) 
@(link_name="odin_add")
add :: proc"system"(a,b :f32) -> f32 {
    context=g_context
    sum : f32 = a + b
    fmt.println("Adding:", a, "plus", b, "=", sum)
    return sum
}
```

Due to this dependency on `main`, everything in the `main` proc is run in WhiteBox.
![image](https://user-images.githubusercontent.com/3990931/203458983-d76fc757-3b94-4211-b78b-714addd2f9b5.png)

A final caveat is that when you recompile your Odin .dll, you will need to completely close out WhiteBox since WhiteBox currently locks the .dll, preventing recompilation.  This should be addressed in a future update. 

Again, this is more of a "Here's Proof That You Can Run Odin With WhiteBox".  
