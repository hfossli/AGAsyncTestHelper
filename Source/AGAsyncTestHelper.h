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



/**
 * @param whileTrue Can be anything
 * @param seconds NSTimeInterval
 */
#define AGWW_STALL_RUNLOOP_WHILE(whileTrue, limitInSeconds)\
({\
    NSDate *giveUpDate = [NSDate dateWithTimeIntervalSinceNow:limitInSeconds];\
    while ((whileTrue) && [giveUpDate timeIntervalSinceNow] > 0)\
    {\
        NSDate *loopIntervalDate = [NSDate dateWithTimeIntervalSinceNow:0.01];\
        [[NSRunLoop currentRunLoop] runUntilDate:loopIntervalDate];\
    }\
})
#ifdef AGWW_SHORTHAND
# define STALL_RUNLOOP_WHILE(whileTrue, limitInSeconds) AGWW_STALL_RUNLOOP_WHILE(whileTrue, limitInSeconds)
#endif

/**
 * @param whileTrue Can be anything
 * @param seconds NSTimeInterval
 * @param ... Description format string (optional)
 */
#define AGWW_WAIT_WHILE(whileTrue, seconds, ...)\
({\
    NSTimeInterval castedLimit = seconds;\
    NSString *conditionString = [NSString stringWithFormat:@"(%s) should NOT be true after async operation completed", #whileTrue];\
    AGWW_STALL_RUNLOOP_WHILE(whileTrue, castedLimit);\
    if(whileTrue)\
    {\
        NSString *description = [NSString stringWithFormat:@"" __VA_ARGS__]; \
        NSString *failString = _agww_makeFailString(conditionString, castedLimit, description, ##__VA_ARGS__);\
        _AGWW_FAIL(@"%@", failString);\
    }\
})
#ifdef AGWW_SHORTHAND
# define WAIT_WHILE(whileTrue, seconds, ...) AGWW_WAIT_WHILE(whileTrue, seconds, ##__VA_ARGS__)
#endif

/**
 * @param value1 Primitive value
 * @param value2 Other primitive value (must be same type as 'value1')
 * @param seconds NSTimeInterval
 * @param ... Description format string (optional)
 */
#define AGWW_WAIT_WHILE_EQUALS(value1, value2, limitInSeconds, ...)\
({\
    _AGWW_ASSERT_SAME_TYPE(value1, value2);\
    NSTimeInterval castedLimit = limitInSeconds;\
    \
    AGWW_STALL_RUNLOOP_WHILE(value1 == value2, castedLimit);\
    if(value1 == value2)\
    {\
        NSString *description = [NSString stringWithFormat:@"" __VA_ARGS__]; \
        NSString *conditionString = _AGWW_VALUE_EQUALITY_FAIL_STRING(value1, @"should not be equal to", value2, 0);\
        NSString *failString = _agww_makeFailString(conditionString, castedLimit, description, ##__VA_ARGS__);\
        _AGWW_FAIL(@"%@", failString);\
    }\
})
#ifdef AGWW_SHORTHAND
# define WAIT_WHILE_EQUALS(value1, value2, limitInSeconds, ...) AGWW_WAIT_WHILE_EQUALS(value1, value2, limitInSeconds, ##__VA_ARGS__)
#endif

/**
 * @param value1 Primitive value
 * @param value2 Other primitive value (must be same type as 'value1')
 * @param accuracy Primitive value
 * @param seconds NSTimeInterval
 * @param ... Description format string (optional)
 */
#define AGWW_WAIT_WHILE_EQUALS_WITH_ACCURACY(value1, value2, accuracy, limitInSeconds, ...)\
({\
    _AGWW_ASSERT_SAME_TYPE(value1, value2);\
    _AGWW_ASSERT_SAME_TYPE(value1, accuracy);\
    NSTimeInterval castedLimit = limitInSeconds;\
    \
    AGWW_STALL_RUNLOOP_WHILE(_AGWW_ABSOLUTE_DIFFERENCE(value1, value2) < accuracy, castedLimit);\
    if(_AGWW_ABSOLUTE_DIFFERENCE(value1, value2) < accuracy)\
    {\
        NSString *description = [NSString stringWithFormat:@"" __VA_ARGS__]; \
        NSString *conditionString = _AGWW_VALUE_EQUALITY_FAIL_STRING(value1, @"should be equal to", value2, accuracy);\
        NSString *failString = _agww_makeFailString(conditionString, castedLimit, description, ##__VA_ARGS__);\
        _AGWW_FAIL(@"%@", failString);\
    }\
})
#ifdef AGWW_SHORTHAND
# define WAIT_WHILE_EQUALS_WITH_ACCURACY(value1, value2, accuracy, limitInSeconds, ...) AGWW_WAIT_WHILE_EQUALS_WITH_ACCURACY(value1, value2, accuracy, limitInSeconds, ##__VA_ARGS__)
#endif

/**
 * @param value1 Primitive value
 * @param value2 Other primitive value (must be same type as 'value1')
 * @param seconds NSTimeInterval
 * @param ... Description format string (optional)
 */
#define AGWW_WAIT_WHILE_NOT_EQUALS(value1, value2, limitInSeconds, ...)\
({\
    _AGWW_ASSERT_SAME_TYPE(value1, value2);\
    NSTimeInterval castedLimit = limitInSeconds;\
    \
    AGWW_STALL_RUNLOOP_WHILE(value1 != value2, castedLimit);\
    if(value1 != value2)\
    {\
        NSString *description = [NSString stringWithFormat:@"" __VA_ARGS__]; \
        NSString *conditionString = _AGWW_VALUE_EQUALITY_FAIL_STRING(value1, @"should not be equal to", value2, 0);\
        NSString *failString = _agww_makeFailString(conditionString, castedLimit, description, ##__VA_ARGS__);\
        _AGWW_FAIL(@"%@", failString);\
    }\
})
#ifdef AGWW_SHORTHAND
# define WAIT_WHILE_NOT_EQUALS(value1, value2, limitInSeconds, ...) AGWW_WAIT_WHILE_NOT_EQUALS(value1, value2, limitInSeconds, ##__VA_ARGS__)
#endif



/**
 * @param value1 Primitive value
 * @param value2 Other primitive value (must be same type as 'value1')
 * @param accuracy Primitive value
 * @param seconds NSTimeInterval
 * @param ... Description format string (optional)
 */
#define AGWW_WAIT_WHILE_NOT_EQUALS_WITH_ACCURACY(value1, value2, accuracy, limitInSeconds, ...)\
({\
    _AGWW_ASSERT_SAME_TYPE(value1, value2);\
    _AGWW_ASSERT_SAME_TYPE(value1, accuracy);\
    NSTimeInterval castedLimit = limitInSeconds;\
    \
    AGWW_STALL_RUNLOOP_WHILE(_AGWW_ABSOLUTE_DIFFERENCE(value1, value2) > accuracy, castedLimit);\
    if(_AGWW_ABSOLUTE_DIFFERENCE(value1, value2) > accuracy)\
    {\
        NSString *description = [NSString stringWithFormat:@"" __VA_ARGS__]; \
        NSString *conditionString = _AGWW_VALUE_EQUALITY_FAIL_STRING(value1, @"should be equal to", value2, accuracy);\
        NSString *failString = _agww_makeFailString(conditionString, castedLimit, description, ##__VA_ARGS__);\
        _AGWW_FAIL(@"%@", failString);\
    }\
})
#ifdef AGWW_SHORTHAND
# define WAIT_WHILE_EQUALS_WITH_ACCURACY(value1, value2, accuracy, limitInSeconds, ...) AGWW_WAIT_WHILE_EQUALS_WITH_ACCURACY(value1, value2, accuracy, limitInSeconds, ##__VA_ARGS__)
#endif

#if defined( XCTFail )
# define _AGWW_FAIL(...) XCTFail(__VA_ARGS__);
#elif defined( STFail )
# define _AGWW_FAIL(...) STFail(__VA_ARGS__);
#else
# error "Missing import of either SenTestingKit or XCTest. Please check that your testclass which is importing AGAsyncTestHelper.h is actually importing the desired test framework."
#endif

#define _AGWW_IS_DIFFERENT_TYPE(a1, a2) strcmp(@encode(__typeof__(a1)), @encode(__typeof__(a2))) != 0

#define _AGWW_ASSERT_SAME_TYPE(a1, a2) {\
    if(_AGWW_IS_DIFFERENT_TYPE(a1, a2)) {\
        _AGWW_FAIL(@"Type mismatch: %s is not same type as %s", #a1, #a2);\
    }\
}

#if __has_feature(objc_arc)
# define _AGWW_RETAIN(xx)            xx
# define _AGWW_RELEASE(xx)           xx
# define _AGWW_AUTORELEASE(xx)       xx
#else
# define _AGWW_RETAIN(xx)            [xx retain]
# define _AGWW_RELEASE(xx)           [xx release]
# define _AGWW_AUTORELEASE(xx)       [xx autorelease]
#endif

// TODO: should be replaced with
// https://github.com/JensAyton/JAValueToString

#define _AGWW_PRIMITIVE_AS_STRING(value) \
({\
    const char *valueType = @encode(__typeof__(value));\
    NSString *format = [NSString stringWithFormat:@"%s", _agww_printFormatTypeForObjCType(valueType)];\
    NSString *valueAsString = [NSString stringWithFormat:format, value];\
    valueAsString;\
})

#define _AGWW_VALUE_EQUALITY_FAIL_STRING(value1, glue, value2, accuracy) \
({\
    NSString *stringValue1 = _AGWW_PRIMITIVE_AS_STRING(value1);\
    NSString *stringValue2 = _AGWW_PRIMITIVE_AS_STRING(value2);\
    \
    NSString *reason;\
    if (accuracy) {\
        reason = [NSString stringWithFormat:@"'%s' (%@) %@ '%s' (%@)", #value1, stringValue1, glue, #value2, stringValue2];\
    } else {\
        NSString *stringAccuracy = _AGWW_PRIMITIVE_AS_STRING(accuracy);\
        reason = [NSString stringWithFormat:@"'%s' (%@) %@ '%s' (%@) +/-'%@'", #value1, stringValue1, glue, #value2, stringValue2, stringAccuracy];\
    }\
    reason;\
})

#define _AGWW_ABSOLUTE_DIFFERENCE(left,right) (MAX(left,right)-MIN(left,right))

static NSString * _agww_makeFailString(NSString *conditionString, NSTimeInterval seconds, NSString *description, ...) {
    va_list args;
    va_start(args, description);
    
    NSString *outputFormat = [NSString stringWithFormat:@"Async test didn't complete within %.2f seconds. %@. %@", (NSTimeInterval) seconds, conditionString, description];
    NSString *outputString = _AGWW_AUTORELEASE([[NSString alloc] initWithFormat:outputFormat arguments:args]);
    va_end(args);
    
    return outputString;
}

static const char * _agww_printFormatTypeForObjCType(const char *type)
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
