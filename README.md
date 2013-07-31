# AGAsyncTestHelper

C Macro for writing unit tests with asynchronous operations. Works perfectly with SenTestingKit!

### Example

    - (void)testDoSomeOperation
    {
        __block BOOL jobDone = NO;
    
        [Manager doSomeOperationOnDone:^(id data) {
            jobDone = YES; 
        }];
    
        WAIT_WHILE(!jobDone, 2.0);
    }

`WAIT_WHILE()` will stall current runloop while `!jobDone` is `TRUE` and throw an `STFail` if exceeding time limit (2.0 seconds)

### Advantages

- Minimum code
- Error thrown *in the test*. Since it is based on macro's the exception will not be thrown in some 3rd party implementation file further down the stack
- Small library
- Works perfectly with SenTestingKit
- No known bugs or issues

### Overview

The macro will evaluate the expression while the expression is true **or** the time limit is reached.

These macros will generate STFail() if time limit is reached.
     
    WAIT_WHILE(expressionIsTrue, limitInSeconds)
    WAIT_WHILE_WITH_DESC(expressionIsTrue, seconds, description, ...)
    WAIT_WHILE_EQUALS(value1, value2, limitInSeconds)
    WAIT_WHILE_EQUALS_WITH_DESC(value1, value2, limitInSeconds, description, ...)
    WAIT_WHILE_EQUALS_WITH_ACCURACY(value1, value2, accuracy, limitInSeconds)
    WAIT_WHILE_EQUALS_WITH_ACCURACY_WITH_DESC(value1, value2, accuracy, limitInSeconds, description, ...)
    WAIT_WHILE_NOT_EQUALS(value, value2, limitInSeconds)
    WAIT_WHILE_NOT_EQUALS_WITH_DESC(value1, value2, limitInSeconds, description, ...)
    AG_STALL_RUNLOPP_WHILE(expressionIsTrue, limitInSeconds)

### Alternatives

You've got several alternatives like

- [SenAsyncTestCase](https://github.com/akisute/SenAsyncTestCase)
- [AssertEventually](https://gist.github.com/lukeredpath/506353/)
- [Kiwi](https://github.com/allending/Kiwi/wiki/Asynchronous-Testing)

There is also a great thread on stack overflow http://stackoverflow.com/questions/4114083/ios-tests-specs-tdd-bdd-and-integration-acceptance-testing


### Cocoa pods
    
Available as 'AGAsyncTestHelper'.

[![Agens | Digital craftsmanship](http://static.agens.no/images/agens_logo_w_slogan_avenir_small.png)](http://agens.no/)
