// This file contains the following Macro sets:
// *** TODO-FIXME-NOTE-MAGIC NUMBERs-NOT IMPLEMENTED-DISABLE_WARNING Macros by Olivier Halligon on 02/10/12.
// *** ColorLogs: IF NOT USING COCOALUMBERJACK: How to apply color formatting to your log statements with Xcode color plugin
// *** Use UIColorFromRGB(rgbValue) macro to set colors from RGB HEX

//
// ----------------------------------------------------------------------
// TODO-FIXME-NOTE-MAGIC NUMBERs-NOT IMPLEMENTED-DISABLE_WARNING Macros.h
// ----------------------------------------------------------------------
//
//  Created by Olivier Halligon on 02/10/12.
//

#define GENERATE_PRAGMA(x) _Pragma(#x)

/* Usage: Use TODO("some message") / FIXME("some message") / NOTE("some message") to generate appropriate warnings */
#define TODO(x) GENERATE_PRAGMA(message("[TODO] " x))
#define FIXME(x) GENERATE_PRAGMA(message("[FIXME] " x))
#define NOTE(x) GENERATE_PRAGMA(message("[NOTE] " x))

/* Usage example:
 *     view.frame = CGRectMake(0, 0, MAGIC_NUMBER(77), MAGIC_NUMBER(90));
 *
 * It will warn you that you should replace values 77 and 90 with constants later, because magic numbers are bad.
 */
#define MAGIC_NUMBER(x) (({ FIXME("Replace magic number " #x " with constant") }), (x))

/* Usage example:
 *     NOT_IMPLEMENTED("This should show the details in a separate screen")
 *
 * Call this in some IBAction that you will implement later, to generate a warning
 * at compile time AND display an alert at runtime if the user trigger the IBAction
 */
#define NOT_IMPLEMENTED(warningMessage) \
        [[[UIAlertView alloc] initWithTitle:[NSString stringWithFormat:@"%s",__PRETTY_FUNCTION__] \
        message:[NSString stringWithFormat:@"%s",warningMessage] \
        delegate:nil cancelButtonTitle:@"OK" otherButtonTitles:nil] show]; \
        TODO("Implement this - " warningMessage)


/* Usage example:
 *     #if TARGET_IPHONE_SIMULATOR
 *     // Use some private API only in simulator to test my app memory mgmt, but _performMemoryWarning
 *     // is a private method so the selector is undeclared so we want to disable the warning
 *     DISABLE_WARNING(undeclared-selector,{
 *       [[UIApplication sharedApplication] performSelector:@selector(_performMemoryWarning)];
 *     })
 *     #endif
 */
#define DISABLE_WARNING(warning,code) \
  GENERATE_PRAGMA(clang diagnostic push) \
  GENERATE_PRAGMA(clang diagnostic ignored "-W" #warning) \
  code \
  GENERATE_PRAGMA(clang diagnostic pop)


// ----------------------------------------------------------------------
// IF NOT USING CocoaLumberJack:
// XcodeColors - How to apply color formatting to your log statements 
// ----------------------------------------------------------------------
// 
// To set the foreground color:
// Insert the ESCAPE_SEQ into your string, followed by "fg124,12,255;" where r=124, g=12, b=255.
// 
// To set the background color:
// Insert the ESCAPE_SEQ into your string, followed by "bg12,24,36;" where r=12, g=24, b=36.
// 
// To reset the foreground color (to default value):
// Insert the ESCAPE_SEQ into your string, followed by "fg;"
// 
// To reset the background color (to default value):
// Insert the ESCAPE_SEQ into your string, followed by "bg;"
// 
// To reset the foreground and background color (to default values) in one operation:
// Insert the ESCAPE_SEQ into your string, followed by ";"


/* UNCOMENT IF NOT USING COCOALUMBERJACK */
/*
#define XCODE_COLORS_ESCAPE_MAC @"\033["
#define XCODE_COLORS_ESCAPE_IOS @"\xC2\xA0["

#if TARGET_OS_IPHONE
  #define XCODE_COLORS_ESCAPE  XCODE_COLORS_ESCAPE_IOS
#else
  #define XCODE_COLORS_ESCAPE  XCODE_COLORS_ESCAPE_MAC
#endif

#define XCODE_COLORS_RESET_FG  XCODE_COLORS_ESCAPE @"fg;" // Clear any foreground color
#define XCODE_COLORS_RESET_BG  XCODE_COLORS_ESCAPE @"bg;" // Clear any background color
#define XCODE_COLORS_RESET     XCODE_COLORS_ESCAPE @";"   // Clear any foreground or background color

#define LogBlue(frmt, ...) NSLog((XCODE_COLORS_ESCAPE @"fg0,0,255;" frmt XCODE_COLORS_RESET), ##__VA_ARGS__)
*/

// ON THE CODE USE FROM THESE EXAMPLES !!!
/*
	NSLog(@"After building the XcodeColors plugin for the first time, you MUST RESTART XCODE.");
	NSLog(@"If you still don't see colors below, please consult the README.");
	
	NSLog(XCODE_COLORS_ESCAPE @"fg0,0,255;" @"Blue text" XCODE_COLORS_RESET);
	
	NSLog(XCODE_COLORS_ESCAPE @"bg220,0,0;" @"Red background" XCODE_COLORS_RESET);
	
	NSLog(XCODE_COLORS_ESCAPE @"fg0,0,255;"
		  XCODE_COLORS_ESCAPE @"bg220,0,0;"
		  @"Blue text on red background"
		  XCODE_COLORS_RESET);
	
	NSLog(XCODE_COLORS_ESCAPE @"fg209,57,168;" @"You can supply your own RGB values!" XCODE_COLORS_RESET);
	
	LogBlue(@"Blue text via macro");
*/


// *** Use UIColorFromRGB(rgbValue) macro to set colors from RGB HEX
#define UIColorFromRGB(rgbValue) [UIColor colorWithRed:((float)((rgbValue & 0xFF0000) >> 16))/255.0 green:((float)((rgbValue & 0xFF00) >> 8))/255.0 blue:((float)(rgbValue & 0xFF))/255.0 alpha:1.0]

