# AGAsyncTestHelper

C Macro for writing unit tests with asynchronous operations on iOS. Supports both SenTestingKit and XCTest.

### Installation
   
Install either `AGAsyncTestHelper` or `AGAsyncTestHelper/Shorthand` with cocoapods. 

### Example blocks

    - (void)testDoSomeOperation
    {
        __block BOOL jobDone = NO;
    
        [Manager doSomeOperationOnDone:^(id data) {
            jobDone = YES; 
        }];
    
        WAIT_WHILE(!jobDone, 2.0);
    }

`WAIT_WHILE()` will stall current runloop while `!jobDone` is `TRUE` and throw an `XCTFail()` if exceeding time limit (2.0 seconds)


### Example plain callback / delegate

    - (void)testDoSomeOperation
    {
        [Manager doSomeOperationOnDoneTellTarget:self selector:@selector(someOperationDone)];
    
        WAIT_WHILE(!self.jobDone, 2.0);
    }
    
    - (void)someOperationDone
    {
        self.jobDone = YES;
    }

`WAIT_WHILE()` will stall current runloop while `!self.jobDone` is `TRUE` and throw an `XCTFail()` or `STFail()` if exceeding time limit (2.0 seconds)

### Overview

The macro will evaluate the expression while the expression is true **or** the time limit is reached.

These macros will generate `XCTFail()` or `STFail()` if time limit is reached.
     
    WAIT_WHILE(expressionIsTrue, seconds, ...)
    WAIT_WHILE_EQUALS(value1, value2, limitInSeconds, ...)
    WAIT_WHILE_EQUALS_WITH_ACCURACY(value1, value2, accuracy, limitInSeconds, ...)
    WAIT_WHILE_NOT_EQUALS(value1, value2, limitInSeconds, ...)
    AG_STALL_RUNLOPP_WHILE(expressionIsTrue, limitInSeconds)

### Advantages

- Minimum code
- Error thrown *in the test*. Since it is based on macro's the exception will not be thrown in some 3rd party implementation file further down the stack
- Small library
- Works perfectly with SenTestingKit
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
