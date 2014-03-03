//
// Author: Håvard Fossli <hfossli@agens.no>
//
// Copyright (c) 2013 Agens AS (http://agens.no/)
//
// Permission is hereby granted, free of charge, to any person obtaining a copy
// of this software and associated documentation files (the "Software"), to deal
// in the Software without restriction, including without limitation the rights
// to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
// copies of the Software, and to permit persons to whom the Software is
// furnished to do so, subject to the following conditions:
//
// The above copyright notice and this permission notice shall be included in
// all copies or substantial portions of the Software.
//
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
// AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
// OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
// THE SOFTWARE.

#import <SenTestingKit/SenTestingKit.h>

#define AGWW_SHORTHAND

#import "AGAsyncTestHelper.h"

@interface AGAsyncTestHelperSenTest : SenTestCase {
@private
    BOOL asyncOperationCompleted;
}

@end

@implementation AGAsyncTestHelperSenTest

#pragma mark - Construct and destruct

- (void)setUp
{
    asyncOperationCompleted = NO;
    [super setUp];
}

- (void)tearDown
{
	[super tearDown];   
}

#pragma mark - Tests

- (void)testAGWW_STALL_RUNLOOP_WHILE
{
    __block BOOL value = NO;

    double delayInSeconds = 0.1;
    dispatch_time_t popTime = dispatch_time(DISPATCH_TIME_NOW, (int64_t)(delayInSeconds * NSEC_PER_SEC));
    dispatch_after(popTime, dispatch_get_global_queue(DISPATCH_QUEUE_PRIORITY_LOW, 0), ^(void){
        value = TRUE;
    });

    AGWW_STALL_RUNLOOP_WHILE(!value, (NSTimeInterval)1.0);
    STAssertTrue(value, nil);
}

- (void)testWAIT_WHILE_withCorrectValueAfterDelay
{
    __block BOOL shouldWait = YES;
    __block BOOL didWait = FALSE;
    
    double delayInSeconds = 0.1;
    dispatch_time_t popTime = dispatch_time(DISPATCH_TIME_NOW, (int64_t)(delayInSeconds * NSEC_PER_SEC));
    dispatch_after(popTime, dispatch_get_global_queue(DISPATCH_QUEUE_PRIORITY_LOW, 0), ^(void){
        shouldWait = NO;
        didWait = TRUE;
    });
    
    AGWW_WAIT_WHILE(shouldWait, (NSTimeInterval)1.0);
    STAssertTrue(didWait, nil);
}

- (void)testWAIT_WHILE_withCorrectInitialValue
{
    __block BOOL shouldWait = NO;
    __block BOOL didWait = FALSE;

    double delayInSeconds = 0.1;
    dispatch_time_t popTime = dispatch_time(DISPATCH_TIME_NOW, (int64_t)(delayInSeconds * NSEC_PER_SEC));
    dispatch_after(popTime, dispatch_get_global_queue(DISPATCH_QUEUE_PRIORITY_LOW, 0), ^(void){
        didWait = TRUE;
    });

    AGWW_WAIT_WHILE(shouldWait, (NSTimeInterval)1.0);
    STAssertFalse(didWait, nil);
}

- (void)testWAIT_WHILE_withDescription
{
    __block BOOL shouldWaitFurther = YES;
    __block BOOL didWait = FALSE;
    
    double delayInSeconds = 0.1;
    dispatch_time_t popTime = dispatch_time(DISPATCH_TIME_NOW, (int64_t)(delayInSeconds * NSEC_PER_SEC));
    dispatch_after(popTime, dispatch_get_global_queue(DISPATCH_QUEUE_PRIORITY_LOW, 0), ^(void){
        shouldWaitFurther = NO;
        didWait = TRUE;
    });
    
    AGWW_WAIT_WHILE(shouldWaitFurther, (NSTimeInterval)1.0, @"Test description %i", 12345);
    STAssertTrue(didWait, nil);
}

- (void)testWAIT_WHILE_EQUALS
{
    __block CGFloat value = 2.0;
    __block BOOL didWait = FALSE;
    
    double delayInSeconds = 0.1;
    dispatch_time_t popTime = dispatch_time(DISPATCH_TIME_NOW, (int64_t)(delayInSeconds * NSEC_PER_SEC));
    dispatch_after(popTime, dispatch_get_global_queue(DISPATCH_QUEUE_PRIORITY_LOW, 0), ^(void){
        value = 1;
        didWait = TRUE;
    });
    
    AGWW_WAIT_WHILE_EQUALS(value, 2.0, (NSTimeInterval)1.0);
    STAssertTrue(didWait, nil);
}

- (void)testWAIT_WHILE_EQUALS_withDescription
{
    __block CGFloat value = 2.0;
    __block BOOL didWait = FALSE;
    
    double delayInSeconds = 0.1;
    dispatch_time_t popTime = dispatch_time(DISPATCH_TIME_NOW, (int64_t)(delayInSeconds * NSEC_PER_SEC));
    dispatch_after(popTime, dispatch_get_global_queue(DISPATCH_QUEUE_PRIORITY_LOW, 0), ^(void){
        value = 1;
        didWait = TRUE;
    });
    
    AGWW_WAIT_WHILE_EQUALS(value, 2.0, (NSTimeInterval)1.0, @"Test description %i", 12345);
    STAssertTrue(didWait, nil);
}

- (CGFloat)testValue
{
    return 2.0;
}

- (void)testWAIT_WHILE_EQUALS_WITH_ACCURACY
{
    __block CGFloat value1 = 2.0005f;
    __block BOOL didWait = FALSE;
    
    double delayInSeconds = 0.1;
    dispatch_time_t popTime = dispatch_time(DISPATCH_TIME_NOW, (int64_t)(delayInSeconds * NSEC_PER_SEC));
    dispatch_after(popTime, dispatch_get_global_queue(DISPATCH_QUEUE_PRIORITY_LOW, 0), ^(void){
        value1 = 1;
        didWait = TRUE;
    });
    
    AGWW_WAIT_WHILE_EQUALS_WITH_ACCURACY(value1, [self testValue], (CGFloat)0.001, (NSTimeInterval)1.0);
    STAssertTrue(didWait, nil);
}

- (void)testWAIT_WHILE_EQUALS_WITH_ACCURACY_withDescription
{
    __block CGFloat value1 = 2.0;
    __block BOOL didWait = FALSE;
    
    double delayInSeconds = 0.1;
    dispatch_time_t popTime = dispatch_time(DISPATCH_TIME_NOW, (int64_t)(delayInSeconds * NSEC_PER_SEC));
    dispatch_after(popTime, dispatch_get_global_queue(DISPATCH_QUEUE_PRIORITY_LOW, 0), ^(void){
        value1 = 1;
        didWait = TRUE;
    });
    
    AGWW_WAIT_WHILE_EQUALS_WITH_ACCURACY(value1, 2.0, (CGFloat)0.001, (NSTimeInterval)1.0, @"Test description %i", 12345);
    STAssertTrue(didWait, nil);
}

- (void)testWAIT_WHILE_NOT_EQUALS
{
    __block CGFloat value1 = 1.0;
    __block BOOL didWait = FALSE;
    
    double delayInSeconds = 0.1;
    dispatch_time_t popTime = dispatch_time(DISPATCH_TIME_NOW, (int64_t)(delayInSeconds * NSEC_PER_SEC));
    dispatch_after(popTime, dispatch_get_global_queue(DISPATCH_QUEUE_PRIORITY_LOW, 0), ^(void){
        value1 = 2.0;
        didWait = TRUE;
    });
    
    AGWW_WAIT_WHILE_NOT_EQUALS(value1, 2.0, (NSTimeInterval)1.0);
    STAssertTrue(didWait, nil);
}

- (void)testWAIT_WHILE_NOT_EQUALS_withDescription
{
    __block CGFloat value1 = 1.0;
    __block BOOL didWait = FALSE;
    
    double delayInSeconds = 0.1;
    dispatch_time_t popTime = dispatch_time(DISPATCH_TIME_NOW, (int64_t)(delayInSeconds * NSEC_PER_SEC));
    dispatch_after(popTime, dispatch_get_global_queue(DISPATCH_QUEUE_PRIORITY_LOW, 0), ^(void){
        value1 = 2.0;
        didWait = TRUE;
    });
    
    AGWW_WAIT_WHILE_NOT_EQUALS(value1, 2.0, (NSTimeInterval)1.0, @"Test description %i", 12345);
    STAssertTrue(didWait, nil);
}

- (void)testWAIT_WHILE_NOT_EQUALS_WITH_ACCURACY
{
    CGFloat targetValue = 1.0;
    CGFloat accuracy = 0.5;
    CGFloat increment = 0.05;
    NSUInteger numberOfIterations = 20;
    __block CGFloat value = 0.0;
    __block BOOL didWait = FALSE;

    dispatch_apply(numberOfIterations, dispatch_get_global_queue(DISPATCH_QUEUE_PRIORITY_LOW, 0), ^(size_t i) {
        value += increment;
        didWait = TRUE;
    });

    AGWW_WAIT_WHILE_NOT_EQUALS_WITH_ACCURACY(value, targetValue, accuracy, (NSTimeInterval)1.0);
    STAssertTrue(didWait, nil);
}

- (void)testShortNames
{
    BOOL wait = NO;
    NSTimeInterval maxWaitDuration = 0.2;
    WAIT_WHILE(wait, maxWaitDuration);
    WAIT_WHILE_EQUALS(1, 3, maxWaitDuration);
    WAIT_WHILE_EQUALS_WITH_ACCURACY(0.2, 0.3, 0.01, maxWaitDuration);
    WAIT_WHILE_NOT_EQUALS(1, 1, maxWaitDuration);
}

@end
