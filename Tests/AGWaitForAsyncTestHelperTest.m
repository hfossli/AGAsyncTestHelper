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

#import <XCTest/XCTest.h>
#import "AGWaitForAsyncTestHelper.h"

@interface AGTestCaseDefinesTest : XCTestCase {
@private
    BOOL asyncOperationCompleted;
}

@end

@implementation AGTestCaseDefinesTest

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


- (void)testAGWWAssertSameType
{
    XCTAssertTrue(AGWWISDifferentType(2, 2.0f));
    XCTAssertTrue(AGWWISDifferentType(2.0, 2.0f));
    XCTAssertFalse(AGWWISDifferentType(2.0f, 2.0f));
    XCTAssertFalse(AGWWISDifferentType((int)2.0f, (int)2.0f));
}

- (void)testAG_STALL_RUNLOPP_WHILE
{
    __block BOOL value = NO;
    
    double delayInSeconds = 0.1;
    dispatch_time_t popTime = dispatch_time(DISPATCH_TIME_NOW, (int64_t)(delayInSeconds * NSEC_PER_SEC));
    dispatch_after(popTime, dispatch_get_global_queue(DISPATCH_QUEUE_PRIORITY_LOW, 0), ^(void){
        value = TRUE;
    });
    
    AG_STALL_RUNLOPP_WHILE(!value, (NSTimeInterval)1.0);
    
    XCTAssertTrue(value);
}

- (void)testAGWW_CREATE_FAIL_STRING
{
    float value = 2.0f;
    float equalTo = 3.0f;
    NSString *conditionFormat = [NSString stringWithFormat:@"%s should NOT be equal to %s", "%.2f", "%.1f"];
    NSString *conditionString = [NSString stringWithFormat:conditionFormat, value, equalTo];
    
    {
        NSString *string = AGWW_CREATE_FAIL_STRING(conditionString, 5.0, @"Testdescription with param %f and another %i", 99.0f, 1000);
        XCTAssertEqualObjects(string, @"Spent too much time (5.00 seconds). 2.00 should NOT be equal to 3.0. Testdescription with param 99.000000 and another 1000");
    }
    {
        NSString *string = AGWW_CREATE_FAIL_STRING(conditionString, 5.0, @"Testdescription without params");
        XCTAssertEqualObjects(string, @"Spent too much time (5.00 seconds). 2.00 should NOT be equal to 3.0. Testdescription without params");
    }
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
    
    WAIT_WHILE(shouldWait, (NSTimeInterval)1.0);
    XCTAssertTrue(didWait);
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

    WAIT_WHILE(shouldWait, (NSTimeInterval)1.0);
    XCTAssertFalse(didWait);
}

- (void)testWAIT_WHILE_WITH_DESC
{
    __block BOOL shouldWaitFurther = YES;
    __block BOOL didWait = FALSE;
    
    double delayInSeconds = 0.1;
    dispatch_time_t popTime = dispatch_time(DISPATCH_TIME_NOW, (int64_t)(delayInSeconds * NSEC_PER_SEC));
    dispatch_after(popTime, dispatch_get_global_queue(DISPATCH_QUEUE_PRIORITY_LOW, 0), ^(void){
        shouldWaitFurther = NO;
        didWait = TRUE;
    });
    
    WAIT_WHILE_WITH_DESC(shouldWaitFurther, (NSTimeInterval)1.0, @"Test description %i", 12345);
    XCTAssertTrue(didWait);
}

- (void)testWAIT_WHILE_EQUALS
{
    __block CGFloat value = 2.0f;
    __block BOOL didWait = FALSE;
    
    double delayInSeconds = 0.1;
    dispatch_time_t popTime = dispatch_time(DISPATCH_TIME_NOW, (int64_t)(delayInSeconds * NSEC_PER_SEC));
    dispatch_after(popTime, dispatch_get_global_queue(DISPATCH_QUEUE_PRIORITY_LOW, 0), ^(void){
        value = 1;
        didWait = TRUE;
    });
    
    WAIT_WHILE_EQUALS(value, 2.0f, (NSTimeInterval)1.0);
    XCTAssertTrue(didWait);
}

- (void)testWAIT_WHILE_EQUALS_WITH_DESC
{
    __block CGFloat value = 2.0f;
    __block BOOL didWait = FALSE;
    
    double delayInSeconds = 0.1;
    dispatch_time_t popTime = dispatch_time(DISPATCH_TIME_NOW, (int64_t)(delayInSeconds * NSEC_PER_SEC));
    dispatch_after(popTime, dispatch_get_global_queue(DISPATCH_QUEUE_PRIORITY_LOW, 0), ^(void){
        value = 1;
        didWait = TRUE;
    });
    
    WAIT_WHILE_EQUALS_WITH_DESC(value, 2.0f, (NSTimeInterval)1.0, @"Test description %i", 12345);
    XCTAssertTrue(didWait);
}

- (float)testValue
{
    return 2.0f;
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
    
    WAIT_WHILE_EQUALS_WITH_ACCURACY(value1, [self testValue], 0.001f, (NSTimeInterval)1.0);
    XCTAssertTrue(didWait);
}

- (void)testWAIT_WHILE_EQUALS_WITH_ACCURACY_WITH_DESC
{
    __block CGFloat value1 = 2.0f;
    __block BOOL didWait = FALSE;
    
    double delayInSeconds = 0.1;
    dispatch_time_t popTime = dispatch_time(DISPATCH_TIME_NOW, (int64_t)(delayInSeconds * NSEC_PER_SEC));
    dispatch_after(popTime, dispatch_get_global_queue(DISPATCH_QUEUE_PRIORITY_LOW, 0), ^(void){
        value1 = 1;
        didWait = TRUE;
    });
    
    WAIT_WHILE_EQUALS_WITH_ACCURACY_WITH_DESC(value1, 2.0f, 0.001f, (NSTimeInterval)1.0, @"Test description %i", 12345);
    XCTAssertTrue(didWait);
}

- (void)testWAIT_WHILE_NOT_EQUALS
{
    __block CGFloat value1 = 1.0f;
    __block BOOL didWait = FALSE;
    
    double delayInSeconds = 0.1;
    dispatch_time_t popTime = dispatch_time(DISPATCH_TIME_NOW, (int64_t)(delayInSeconds * NSEC_PER_SEC));
    dispatch_after(popTime, dispatch_get_global_queue(DISPATCH_QUEUE_PRIORITY_LOW, 0), ^(void){
        value1 = 2.0f;
        didWait = TRUE;
    });
    
    WAIT_WHILE_NOT_EQUALS(value1, 2.0f, (NSTimeInterval)1.0);
    XCTAssertTrue(didWait);
}

- (void)testWAIT_WHILE_NOT_EQUALS_WITH_DESC
{
    __block CGFloat value1 = 1.0f;
    __block BOOL didWait = FALSE;
    
    double delayInSeconds = 0.1;
    dispatch_time_t popTime = dispatch_time(DISPATCH_TIME_NOW, (int64_t)(delayInSeconds * NSEC_PER_SEC));
    dispatch_after(popTime, dispatch_get_global_queue(DISPATCH_QUEUE_PRIORITY_LOW, 0), ^(void){
        value1 = 2.0f;
        didWait = TRUE;
    });
    
    WAIT_WHILE_NOT_EQUALS_WITH_DESC(value1, 2.0f, (NSTimeInterval)1.0, @"Test description %i", 12345);
    XCTAssertTrue(didWait);
}

@end
