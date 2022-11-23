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
