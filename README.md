#WaitForAsyncTestHelper

C Macro to wait for any async test and get an STFail directly in your test.

Example 
------

    __block BOOL jobDone = NO;
    
    [AGLiftManager doSomeAsyncHeavyWork:^{
        jobDone = YES;
    }];
    
    WAIT_FOR_ASYNC_OPERATION_WHILE(!jobDone, 0.2, @"Waited too long");

Cocoa pods
-------
    
It is added to the Cocoa Pods public repository as `WaitForAsyncTestHelper`.

[![Agens | Digital craftsmanship](http://static.agens.no/images/agens_logo_w_slogan_avenir_small.png)](http://agens.no/)
