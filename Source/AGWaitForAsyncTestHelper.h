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

#if __has_feature(objc_arc)
# define AGWW_RETAIN(xx)            xx
# define AGWW_RELEASE(xx)           xx
# define AGWW_AUTORELEASE(xx)       xx
#else
# define AGWW_RETAIN(xx)            [xx retain]
# define AGWW_RELEASE(xx)           [xx release]
# define AGWW_AUTORELEASE(xx)       [xx autorelease]
#endif


/**
 * @param whileTrue Can be anything
 * @param seconds NSTimeInterval
 */
#define AG_STALL_RUNLOPP_WHILE(whileTrue, limitInSeconds) ({\
    NSDate *giveUpDate = [NSDate dateWithTimeIntervalSinceNow:limitInSeconds];\
    while ((whileTrue) && [giveUpDate timeIntervalSinceNow] > 0)\
    {\
        NSDate *loopIntervalDate = [NSDate dateWithTimeIntervalSinceNow:0.01];\
        [[NSRunLoop currentRunLoop] runUntilDate:loopIntervalDate];\
    }\
})

/**
 * @param whileTrue Can be anything
 * @param seconds NSTimeInterval
 */
#define WAIT_WHILE(whileTrue, seconds)\
({\
    WAIT_WHILE_WITH_DESC(whileTrue, seconds, nil);\
})

/**
 * @param whileTrue Can be anything
 * @param seconds NSTimeInterval
 * @param description NSString format
 * @param ... Arguments for description string format
 */
#define WAIT_WHILE_WITH_DESC(whileTrue, seconds, description, ...)\
({\
    NSTimeInterval castedLimit = seconds;\
    NSString *conditionString = [NSString stringWithFormat:@"(%s) should NOT be true after async operation completed", #whileTrue];\
    if(!(whileTrue))\
    {\
        NSString *failString = AGWW_CREATE_FAIL_STRING_1(conditionString, description, ##__VA_ARGS__);\
        STFail(failString);\
    }\
    else\
    {\
        AG_STALL_RUNLOPP_WHILE(whileTrue, castedLimit);\
        if(whileTrue)\
        {\
            NSString *failString = AGWW_CREATE_FAIL_STRING_2(conditionString, castedLimit, description, ##__VA_ARGS__);\
            STFail(failString);\
        }\
    }\
})

/**
 * @param value1 Primitive value
 * @param value2 Other primitive value (must be same type as 'value1')
 * @param seconds NSTimeInterval
 */
#define WAIT_WHILE_EQUALS(value1, value2, limitInSeconds)\
({\
    WAIT_WHILE_EQUALS_WITH_DESC(value1, value2, limitInSeconds, nil);\
})

/**
 * @param value1 Primitive value
 * @param value2 Other primitive value (must be same type as 'value1')
 * @param seconds NSTimeInterval
 * @param description NSString format
 * @param ... Arguments for description string format
 */
#define WAIT_WHILE_EQUALS_WITH_DESC(value1, value2, limitInSeconds, description, ...)\
({\
    AGWWAssertSameType(value1, value2);\
    NSTimeInterval castedLimit = limitInSeconds;\
    \
    if(value1 != value2)\
    {\
        NSString *failString = AGWW_CREATE_FAIL_STRING_1(@"There is nothing to wait for. Values already equal.", description, ##__VA_ARGS__);\
        STFail(failString);\
    }\
    else\
    {\
        AG_STALL_RUNLOPP_WHILE(value1 == value2, castedLimit);\
        if(value1 == value2)\
        {\
            NSString *conditionString = AGWW_VALUE_EQUALITY_FAIL_STRING(value1, @"should not be equal to", value2, 0);\
            NSString *failString = AGWW_CREATE_FAIL_STRING_2(conditionString, castedLimit, description, ##__VA_ARGS__);\
            STFail(failString);\
        }\
    }\
})


/**
 * @param value1 Primitive value
 * @param value2 Other primitive value (must be same type as 'value1')
 * @param accuracy Primitive value
 * @param seconds NSTimeInterval
 */
#define WAIT_WHILE_EQUALS_WITH_ACCURACY(value1, value2, accuracy, limitInSeconds)\
({\
    WAIT_WHILE_EQUALS_WITH_ACCURACY_WITH_DESC(value1, value2, accuracy, limitInSeconds, nil);\
})

/**
 * @param value1 Primitive value
 * @param value2 Other primitive value (must be same type as 'value1')
 * @param accuracy Primitive value
 * @param seconds NSTimeInterval
 * @param description NSString format
 * @param ... Arguments for description string format
 */
#define WAIT_WHILE_EQUALS_WITH_ACCURACY_WITH_DESC(value1, value2, accuracy, limitInSeconds, description, ...)\
({\
    AGWWAssertSameType(value1, value2);\
    AGWWAssertSameType(value1, accuracy);\
    NSTimeInterval castedLimit = limitInSeconds;\
    \
    if(STAbsoluteDifference(value1, value2) > accuracy)\
    {\
        NSString *failString = AGWW_CREATE_FAIL_STRING_1(@"There is nothing to wait for. Values already different.", description, ##__VA_ARGS__);\
        STFail(failString);\
    }\
    else\
    {\
        AG_STALL_RUNLOPP_WHILE(STAbsoluteDifference(value1, value2) < accuracy, castedLimit);\
        if(STAbsoluteDifference(value1, value2) < accuracy)\
        {\
            NSString *conditionString = AGWW_VALUE_EQUALITY_FAIL_STRING(value1, @"should be equal to", value2, accuracy);\
            NSString *failString = AGWW_CREATE_FAIL_STRING_2(conditionString, castedLimit, description, ##__VA_ARGS__);\
            STFail(failString);\
        }\
    }\
})

/**
 * @param value Primitive value
 * @param equalTo Other primitive value (must be same type as 'value1')
 * @param seconds NSTimeInterval
 */
#define WAIT_WHILE_NOT_EQUALS(value, equalTo, limitInSeconds)\
({\
    WAIT_WHILE_NOT_EQUALS_WITH_DESC(value, equalTo, limitInSeconds, nil);\
})

/**
 * @param value1 Primitive value
 * @param value2 Other primitive value (must be same type as 'value1')
 * @param seconds NSTimeInterval
 * @param description NSString format
 * @param ... Arguments for description string format
 */
#define WAIT_WHILE_NOT_EQUALS_WITH_DESC(value1, value2, limitInSeconds, description, ...)\
({\
    AGWWAssertSameType(value1, value2);\
    NSTimeInterval castedLimit = limitInSeconds;\
    \
    if(value1 == value2)\
    {\
        NSString *failString = AGWW_CREATE_FAIL_STRING_1(@"There is nothing to wait for. Values already equal.", description, ##__VA_ARGS__);\
        STFail(failString);\
    }\
    else\
    {\
        AG_STALL_RUNLOPP_WHILE(value1 != value2, castedLimit);\
        if(value1 != value2)\
        {\
            NSString *conditionString = AGWW_VALUE_EQUALITY_FAIL_STRING(value1, @"should not be equal to", value2, 0);\
            NSString *failString = AGWW_CREATE_FAIL_STRING_2(conditionString, castedLimit, description, ##__VA_ARGS__);\
            STFail(failString);\
        }\
    }\
})

static NSString * AGWW_CREATE_FAIL_STRING_1(NSString *conditionString, NSString *description, ...) {
    va_list args;
    va_start(args, description);
    
    NSString *outputFormat = [NSString stringWithFormat:@"Was already right before 'wait' on async operation. %@. %@", conditionString, description];
    NSString *outputString = AGWW_AUTORELEASE([[NSString alloc] initWithFormat:outputFormat arguments:args]);
    va_end(args);

    return outputString;
}

static NSString * AGWW_CREATE_FAIL_STRING_2(NSString *conditionString, NSTimeInterval seconds, NSString *description, ...) {
    va_list args;
    va_start(args, description);
    
    NSString *outputFormat = [NSString stringWithFormat:@"Spent too much time (%.2f seconds). %@. %@", (NSTimeInterval) seconds, conditionString, description];
    NSString *outputString = AGWW_AUTORELEASE([[NSString alloc] initWithFormat:outputFormat arguments:args]);
    va_end(args);
    
    return outputString;
}

#define AGWWISDifferentType(a1, a2) strcmp(@encode(__typeof__(a1)), @encode(__typeof__(a2))) != 0

#define AGWWAssertSameType(a1, a2) {\
    if(AGWWISDifferentType(a1, a2)) {\
        STFail(@"Type mismatch: %s is not same type as %s", #a1, #a2);\
    }\
}

static const char * printFormatTypeForObjCType(const char *type)
{
    if(strcmp(type, @encode(BOOL)) == 0)
        return "%i";
    else if(strcmp(type, @encode(int)) == 0)
        return "%i";
    else if(strcmp(type, @encode(unsigned int)) == 0)
        return "%u";
    else if(strcmp(type, @encode(long)) == 0)
        return "%li";
    else if(strcmp(type, @encode(unsigned long)) == 0)
        return "%lu";
    else if(strcmp(type, @encode(long long)) == 0)
        return "%lli";
    else if(strcmp(type, @encode(unsigned long long)) == 0)
        return "%llu";
    else if(strcmp(type, @encode(float)) == 0)
        return "%f";
    else if(strcmp(type, @encode(double)) == 0)
        return "%d";
    else
        return "%i";
}

// TODO: should be replaced with
// https://github.com/JensAyton/JAValueToString

#define AGWW_PRIMITIVE_AS_STRING(value) \
({\
    const char *valueType = @encode(__typeof__(value));\
    NSString *format = [NSString stringWithFormat:@"%s", printFormatTypeForObjCType(valueType)];\
    NSString *valueAsString = [NSString stringWithFormat:format, value];\
    valueAsString;\
})

#define AGWW_VALUE_EQUALITY_FAIL_STRING(value1, glue, value2, accuracy) \
({\
    NSString *stringValue1 = AGWW_PRIMITIVE_AS_STRING(value1);\
    NSString *stringValue2 = AGWW_PRIMITIVE_AS_STRING(value2);\
    \
    NSString *reason;\
    if (accuracy) {\
        reason = [NSString stringWithFormat:@"'%s' (%@) %@ '%s' (%@).", #value1, stringValue1, glue, #value2, stringValue2];\
    } else {\
        NSString *stringAccuracy = AGWW_PRIMITIVE_AS_STRING(accuracy);\
        reason = [NSString stringWithFormat:@"'%s' (%@) %@ '%s' (%@) +/-'%@'.", #value1, stringValue1, glue, #value2, stringValue2, stringAccuracy];\
    }\
    reason;\
})

