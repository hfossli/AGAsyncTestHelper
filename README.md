# AGAsyncTestHelper

C Macro for writing unit tests with asynchronous operations on iOS. Supports both SenTestingKit and XCTest.




### Installation by Cocoapods
   
Install either `AGAsyncTestHelper` or `AGAsyncTestHelper/Shorthand` with cocoapods. The latter one lets you write `WAIT_WHILE()` instead of `AGWW_WAIT_WHILE()`.


### Manual installation

Copy the files found in `Source` over to your project. 

If you want to have shorthand enabled (`WAIT_WHILE()` instead of `AGWW_WAIT_WHILE()`) you can either create a *User Defined Build Setting* within Xcode named `AGWW_SHORTHAND` OR write `#define AGWW_SHORTHAND` some clever place in your testsuite.


### Overview

The macro will evaluate the expression (the first parameter) until expression is not longer true **or** the time limit is reached.

These macros will generate `XCTFail()` or `STFail()` if time limit is reached.
     
    WAIT_WHILE(<expression_to_evaluate>, limit_in_seconds, ...)
    WAIT_WHILE_EQUALS(<value1>, <value2>, limit_in_seconds, ...)
    WAIT_WHILE_EQUALS_WITH_ACCURACY(<value1>, <value2>, accuracy, limit_in_seconds, ...)
    WAIT_WHILE_NOT_EQUALS(<value1>, <value2>, limit_in_seconds, ...)
    STALL_RUNLOPP_WHILE(<expression_to_evaluate>, limit_in_seconds)





### Example: Wait for block callback

```
- (void)testAsyncBlockCallback
{
    __block BOOL jobDone = NO;

    [Manager doSomeOperationOnDone:^(id data) {
        jobDone = YES; 
    }];

    WAIT_WHILE(!jobDone, 2.0);
}
```

`WAIT_WHILE()` will stall current runloop while `!jobDone` is `TRUE` and throw an `XCTFail()` if exceeding time limit (2.0 seconds)





### Example: Wait for delegate callback

```
- (void)testAsyncDelegateCallback
{
    Manager *manager = [Manager new];
    manager.delegate = self;
    [manager doSomeOperation];

    WAIT_WHILE(!self.jobDone, 2.0);
}

- (void)someOperationIsDoneInManager:(Manager *)manager
{
    self.jobDone = YES;
}
```
`WAIT_WHILE()` will stall current runloop while `!self.jobDone` is `TRUE` and throw an `XCTFail()` or `STFail()` if exceeding time limit (2.0 seconds)






### Example: Wait for @selector callback

```
- (void)testAsyncSelectorCallback
{
    [Manager doSomeOperationOnDoneTellTarget:self selector:@selector(someOperationIsDone)];

    WAIT_WHILE(!self.jobDone, 2.0);
}

- (void)someOperationIsDone
{
    self.jobDone = YES;
}
```

`WAIT_WHILE()` will stall current runloop while `!self.jobDone` is `TRUE` and throw an `XCTFail()` or `STFail()` if exceeding time limit (2.0 seconds)






### Example: Multiple values will eventually be right

```
- (void)testMultipleWillEventuallyBeRight
{
    UIImage *image = ...;
    [[ImageManager shared] saveImage:image];

    BOOL (^cacheIsPurged) = ^{
        UIImage *cachedMemoryImage = [[ImageManager shared] imageFromMemoryCacheForKey:@"IMAGE_KEY"];
        UIImage *cachedDiskImage = [[ImageManager shared] imageFromDiskCacheForKey:@"IMAGE_KEY"];
        return cachedMemoryImage || cachedDiskImage;
    };

    [[ImageManager shared] purgeCacheAsync];

    WAIT_WHILE(!cacheIsPurged(), 5.0, @"Failed to clean up image cache!");
}
```
`WAIT_WHILE()` will stall current runloop while `!cacheIsPurged()` is `TRUE` and throw an `XCTFail()` or `STFail()` if exceeding time limit (5.0 seconds)




### Under the hood

A simplified version of how the macro works could look like this

```
__block BOOL done = NO;
doSomethingAsynchronouslyWithBlock(^{
    done = YES;
});

while(!done) {
   [[NSRunLoop currentRunLoop] runMode:NSDefaultRunLoopMode beforeDate:[NSDate distantFuture]];
}
```

Effectively stalling the runloop until `done` is true. This does not block the main thread so you are still able to have callbacks on the main thread. 





### Advantages

- Minimum code
- Error thrown *in the test*. Since it is based on macro's the exception will not be thrown in some 3rd party implementation file further down the stack
- Small library
- Works perfectly with SenTestingKit and XCTest (could easily support more)
- No known bugs or issues




### Alternatives

You've got several alternatives like

- [SenAsyncTestCase](https://github.com/akisute/SenAsyncTestCase)
- [AssertEventually](https://gist.github.com/lukeredpath/506353/)
- [Kiwi](https://github.com/allending/Kiwi/wiki/Asynchronous-Testing)
- [SenTestCase+SRTAdditions](https://github.com/square/SocketRocket/blob/master/SRWebSocketTests/SenTestCase+SRTAdditions.h)
- [SenTestingKitAsync](https://github.com/nxtbgthng/SenTestingKitAsync)

If you've got other alternatives which should be listed here please let me know.

There is also a great thread on stack overflow http://stackoverflow.com/questions/4114083/ios-tests-specs-tdd-bdd-and-integration-acceptance-testing





### Extensive description

This library or bundle enables you to do async test operations with asynchronous callbacks in your SenTestCase. Works with GCD (Grand Central Dispatch) and regular delegate callbacks. 

[![Agens | Digital craftsmanship](http://static.agens.no/images/agens_logo_w_slogan_avenir_small.png)](http://agens.no/)
