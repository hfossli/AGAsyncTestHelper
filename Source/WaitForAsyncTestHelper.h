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

#define _AGISDifferentType(a1, a2) strcmp(@encode(__typeof__(a1)), @encode(__typeof__(a2))) != 0

#define _AG_STALL_RUNLOPP_WHILE(whileTrue, limitInSeconds) ({\
    NSDate *giveUpDate = [NSDate dateWithTimeIntervalSinceNow:limitInSeconds];\
    while ((whileTrue) && [giveUpDate timeIntervalSinceNow] > 0)\
    {\
        NSDate *loopIntervalDate = [NSDate dateWithTimeIntervalSinceNow:0.01];\
        [[NSRunLoop currentRunLoop] runUntilDate:loopIntervalDate];\
    }\
})

#define _AGAssertSameType(a1, a2) {\
    if(_AGISDifferentType(a1, a2)) {\
        STFail(@"Type mismatch: %s is not same type as %s", #a1, #a2);\
    }\
}

static NSString * _AG_CREATE_FAIL_STRING_1(NSString *conditionString, NSString *description, ...) {
    va_list args;
    va_start(args, description);
    
    NSString *outputFormat = [NSString stringWithFormat:@"Was already right before 'wait' on async operation. %@. %@.", conditionString, description];
    NSString *outputString = [[NSString alloc] initWithFormat:outputFormat arguments:args];
    va_end(args);

    return outputString;
}

static NSString * _AG_CREATE_FAIL_STRING_2(NSString *conditionString, NSTimeInterval seconds, NSString *description, ...) {
    va_list args;
    va_start(args, description);
    
    NSString *outputFormat = [NSString stringWithFormat:@"Spent too much time (%.1f seconds). %@. %@.", (NSTimeInterval) seconds, conditionString, description];
    NSString *outputString = [[NSString alloc] initWithFormat:outputFormat arguments:args];
    va_end(args);
    
    return outputString;
}

#define WAIT_FOR_ASYNC_OPERATION(limitInSeconds, description, ...)\
{\
    NSTimeInterval castedLimit = limitInSeconds;\
    NSString *descriptionString = description == nil ? @"" : [NSString stringWithFormat:description, ##__VA_ARGS__];\
    if(asyncOperationCompleted)\
    {\
        STFail([NSString stringWithFormat:@"asyncOperationCompleted == TRUE before wait!. %@", descriptionString]);\
    }\
    else\
    {\
        _AG_STALL_RUNLOPP_WHILE(!asyncOperationCompleted, castedLimit);\
        if(!asyncOperationCompleted)\
        {\
            STFail([NSString stringWithFormat:@"Spent too much time (%.1f seconds).. %@", castedLimit, descriptionString]);\
        }\
    }\
}

#define WAIT_FOR_ASYNC_OPERATION_WHILE_EQUALS(value, equalTo, typeSpeficier, limitInSeconds, description, ...)\
{\
    _AGAssertSameType(value, equalTo);\
    NSTimeInterval castedLimit = limitInSeconds;\
    NSString *conditionFormat = [NSString stringWithFormat:@"%s should NOT be equal to %s", #typeSpeficier, #typeSpeficier];\
    NSString *conditionString = [NSString stringWithFormat:conditionFormat, value, equalTo];\
    if(value != equalTo)\
    {\
        NSString *failString = _AG_CREATE_FAIL_STRING_1(conditionString, description, ##__VA_ARGS__);\
        STFail(failString);\
    }\
    else\
    {\
        _AG_STALL_RUNLOPP_WHILE(value == equalTo, castedLimit);\
        if(value == equalTo)\
        {\
            NSString *failString = _AG_CREATE_FAIL_STRING_2(conditionString, castedLimit, description, ##__VA_ARGS__);\
            STFail(failString);\
        }\
    }\
}

#define WAIT_FOR_ASYNC_OPERATION_WHILE_NOT_EQUALS(value, equalTo, typeSpeficier, limitInSeconds, description, ...)\
{\
    _AGAssertSameType(value, equalTo);\
    NSTimeInterval castedLimit = limitInSeconds;\
    NSString *conditionFormat = [NSString stringWithFormat:@"%s should be equal to %s", #typeSpeficier, #typeSpeficier];\
    NSString *conditionString = [NSString stringWithFormat:conditionFormat, value, equalTo];\
    if(value == equalTo)\
    {\
        NSString *failString = _AG_CREATE_FAIL_STRING_1(conditionString, description, ##__VA_ARGS__);\
        STFail(failString);\
    }\
    else\
    {\
        _AG_STALL_RUNLOPP_WHILE(value != equalTo, castedLimit);\
        if(value != equalTo)\
        {\
            NSString *failString = _AG_CREATE_FAIL_STRING_2(conditionString, castedLimit, description, ##__VA_ARGS__);\
            STFail(failString);\
        }\
    }\
}

#define WAIT_FOR_ASYNC_OPERATION_WHILE(whileTrue, seconds, description, ...)\
{\
    NSTimeInterval castedLimit = seconds;\
    NSString *conditionString = [NSString stringWithFormat:@"(%s) should NOT be true after async operation completed", #whileTrue];\
    if(!(whileTrue))\
    {\
        NSString *failString = _AG_CREATE_FAIL_STRING_1(conditionString, description, ##__VA_ARGS__);\
        STFail(failString);\
    }\
    else\
    {\
        _AG_STALL_RUNLOPP_WHILE(whileTrue, castedLimit);\
        if(whileTrue)\
        {\
            NSString *failString = _AG_CREATE_FAIL_STRING_2(conditionString, castedLimit, description, ##__VA_ARGS__);\
            STFail(failString);\
        }\
    }\
}

