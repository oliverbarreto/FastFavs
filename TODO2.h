// TODO List for a new iOS Project 
// Oliver Barreto 2013-12-15
// For instructinos and how to use go to HOWTO Section at the end of this file 


//------------------
// TODO LIST 
//------------------

//------------------------------------------------------------------------
//
// Create a new project in Xcode

//------------------------------------------------------------------------
//
// Drag and copy folder structure to Xcode inside MYPROJECT folder my "iOS New Xcode Project Template" folder: 
// Classes, Resources, .gitattributes, .gitignore and Podfile (needs editing!!!)

//------------------------------------------------------------------------
//
// Podfile: Create/Edit  CocoaPod file to include libraries that will be used... 
// CocoaLumberJack & Testflight... otros
// Use sublime text snippet "iospodfile" to create the file... 
// Install it using "pod install" or update "pod update"
/* platform :ios, "7.0"

target "MiProyecto" do
  pod 'AFNetworking'
  pod 'CocoaLumberjack'
  pod 'TestFlightSDK'
  pod 'TestFlightLogger'
  pod 'Reachability'
end
target "MiProyectoTests" do

end

inhibit_all_warnings!
*/

//------------------------------------------------------------------------
//
// Edit Prefix.pch file to include the following
/*
#ifdef __OBJC__
    #import <UIKit/UIKit.h>
    #import <Foundation/Foundation.h>
	// Import CocoaLumberJack
	#import <DDLog.h>
	//Import TestFlight if using TestFlight
	#import <TestFlight.h>
	#import <TestFlightLogger.h>
    //Import DOBRCustomMarcrosFile.h
    #import "DOBRCustomMacrosFile.h"
#endif

// At the end of the Prefix.pch
// Add LogLevel for CocoaLumberJack

#ifdef DEBUG
  static const int ddLogLevel = LOG_LEVEL_VERBOSE;
#else
  static const int ddLogLevel = LOG_LEVEL_WARN;
#endif

*/

//------------------------------------------------------------------------
//
// Edit AppDelegate application:didFinishLaunchingWithOptions: to include:
// a) CocoaLumberJack Loggers
// b) SETUP Colors for CocoaLumberjack Dlogs using XcodeColors... to setup do:
// In Xcode bring up the Scheme Editor (Product -> Edit Scheme...),
// Select "Run" (on the left), and then the "Arguments" tab,
// Add a new Environment Variable named "XcodeColors", with a value of "YES"
// https://github.com/robbiehanson/XcodeColors
// It's nice if you have also installed ColorSense-for-Xcode
// https://github.com/omz/ColorSense-for-Xcode



// In APPDELEGATE.m

// Import CocoaLumberJack Loger for Xcode console
	#import <DDTTYLogger.h>
  // ...



- (BOOL)application:(UIApplication *)application didFinishLaunchingWithOptions:(NSDictionary *)launchOptions
   // With these 2 lines of code we send logs to Xcode console (DDTTYLogger) and Testfligh servers (TestFlightLogger)
  // TestFlight setup
  [TestFlight takeOff:@"YOUR-APP-TOKEN-GOES-HERE"];

  // CocoaLumberjack setup
  [DDLog addLogger:[TestFlightLogger sharedInstance]];
  [DDLog addLogger:[DDTTYLogger sharedInstance]];
  
    // SETUP Colors for CocoaLumberjack Dlogs... Now you can even change the color of a certain level
    [[DDTTYLogger sharedInstance] setColorsEnabled:YES];
    [[DDTTYLogger sharedInstance] setForegroundColor:[UIColor greenColor] backgroundColor:nil forFlag:LOG_FLAG_INFO];
    [[DDTTYLogger sharedInstance] setForegroundColor:[UIColor orangeColor] backgroundColor:nil forFlag:LOG_FLAG_WARN];
    [[DDTTYLogger sharedInstance] setForegroundColor:[UIColor redColor] backgroundColor:nil forFlag:LOG_FLAG_ERROR];
    [[DDTTYLogger sharedInstance] setForegroundColor:[UIColor whiteColor] backgroundColor:nil forFlag:LOG_LEVEL_VERBOSE];



    // Put the rest of your dance here ...

}



//------------------------------------------------------------------------
//
// Edit Prefix.pch to include macros that handle Logs and Asserts
// Orifinal macros by Marcus Zarra without sending Checkpoints to TestFlight Servers
// http://www.cimgf.com/2010/05/02/my-current-prefix-pch-file/

#ifdef DEBUG
  #define DLog(...) NSLog(@"%s %@", __PRETTY_FUNCTION__, [NSString stringWithFormat:__VA_ARGS__])
  #define ALog(...) [[NSAssertionHandler currentHandler] handleFailureInFunction:[NSString stringWithCString:__PRETTY_FUNCTION__ encoding:NSUTF8StringEncoding] file:[NSString stringWithCString:__FILE__ encoding:NSUTF8StringEncoding] lineNumber:__LINE__ description:__VA_ARGS__]
#else
  #define DLog(...) do { } while (0)
  #ifndef NS_BLOCK_ASSERTIONS
    #define NS_BLOCK_ASSERTIONS
  #endif
  #define ALog(...) NSLog(@"%s %@", __PRETTY_FUNCTION__, [NSString stringWithFormat:__VA_ARGS__])
#endif
 
#define ZAssert(condition, ...) do { if (!(condition)) { ALog(__VA_ARGS__); }} while(0)


//
// If we want to use TestFlight Checkpoints use the following macros provided by @sendoa at 
// http://www.punteroavoid.com/blog/2013/07/12/iniciando-un-nuevo-proyecto-ios/
// https://gist.github.com/sendoa/5961029

#ifdef DEBUG
    #define DLog(...) NSLog(@"%s %@", __PRETTY_FUNCTION__, [NSString stringWithFormat:__VA_ARGS__])
    #define ALog(...) [[NSAssertionHandler currentHandler] handleFailureInFunction:[NSString stringWithCString:__PRETTY_FUNCTION__ encoding:NSUTF8StringEncoding] file:[NSString stringWithCString:__FILE__ encoding:NSUTF8StringEncoding] lineNumber:__LINE__ description:__VA_ARGS__]
#else
    #define DLog(...) do { } while (0)
    #define ALog(...) [TestFlight passCheckpoint:[NSString stringWithFormat:__VA_ARGS__]]
    #ifndef NS_BLOCK_ASSERTIONS
        #define NS_BLOCK_ASSERTIONS
    #endif
#endif

#define ZAssert(condition, ...) do { if (!(condition)) { ALog(__VA_ARGS__); }} while(0)


//------------------------------------------------------------------------
//
// IF NOT USING CocoaLumberJack:
// XcodeColors - How to apply color formatting to your log statements 
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



//------------------------------------
// HOWTO SECTION
//------------------------------------
//
//------------------------------------
// CocoaLumberJack Logging Usage
//------------------------------------
// https://github.com/CocoaLumberjack/CocoaLumberjack
/* 
Con esto hacemos que los mensajes de log se envíen a la consola de Xcode (DDTTYLogger) y a nuestro panel de TestFlight (TestFlightLogger). Para lanzar un mensaje de log con CocoaLumberjack:

DDLogError(@"Mensaje de log con nivel de error");
DDLogWarn(@"Mensaje de log con nivel de warning");
DDLogInfo(@"Mensaje de log con nivel de info");
DDLogDebug();
DDLogVerbose(@"User selected file:%@ withSize:%u", filePath, fileSize);

En modo Debug se procesarán los tres mensajes pero en modo Release tan solo se procesarán los dos primeros porque hemos indicado un log level de nivel LOG_LEVEL_WARN en adelante. 
La prioridad es la siguiente (texto directamente obtenido de la documentación de CocoaLumberjack
https://github.com/CocoaLumberjack/CocoaLumberjack/wiki/GettingStarted


- If you set the log level to LOG_LEVEL_ERROR, then you will only see DDLogError statements.
- If you set the log level to LOG_LEVEL_WARN, then you will only see DDLogError and DDLogWarn statements.
- If you set the log level to LOG_LEVEL_INFO, you’ll see Error, Warn and Info statements.
- If you set the log level to LOG_LEVEL_VERBOSE, you’ll see all DDLog statements.
- If you set the log level to LOG_LEVEL_OFF, you won’t see any DDLog statements.
*/


//------------------------------------
// LOG & Asserts Management Macros
//------------------------------------
//
// +1 Thanks to sendoa (http://www.punteroavoid.com/blog/2013/07/12/iniciando-un-nuevo-proyecto-ios/) for sharing his knowledge !!!
// NSLog and NSAssert substitution macros based on the ones from Marcus Zarra 
// http://www.cimgf.com/2010/05/02/my-current-prefix-pch-file/ 
//
//When the app runs on "Release" mode, assertions are linked to TestFlight checkpoints. 
// I always name assertion type checkpoints with "ASSERTION" prefix. 
//Example: Alog(@"ASSERTION_NON_PARSEABLE_ITEM_DATA_RECEIVED");
/* Con estas macros consigo lo siguiente:
- Puedo lanzar NSAssert-s de forma directa, sin condición, a través de Alog.
- Puedo lanzar NSAsserts con condición a través de ZAssert.
- Si estamos en modo Debug los asserts hacen que la app casque al momento. En modo Release la app no peta sino que lanza un DDLogWarn que será enviado a TestFlight.

// IMPORTANT !!!
ORIGINAL MACROS http://www.cimgf.com/2010/05/02/my-current-prefix-pch-file/
Estas macros las podemos meter directamente dentro de nuestro Prefix.pch. 
Yo las tengo dentro de un archivo llamado Dlog.h que copio dentro de mis proyectos y que está referenciado en Prefix.pch !!!

El problema con esta implementación es que los mensajes de log que se envían a TestFlight quedan ocultos a cierta profundidad en la interfaz, con lo cual, no son visibles de forma inmediata. Yo quiero que los asserts alcanzados en Release sean bien visibles. Para solucionarlo decidí cambiar la implementación de la macro ALog para el modo Release:
Con este cambio, en lugar de enviar un mensaje de log, envío una señal de checkpoint alcanzado. Los checkpoints de TestFlight permiten establecer hitos a lo largo de nuestra aplicación para saber a qué lugares llega el usuario, qué botones pulsa, a qué secciones entra, etc. Los checkpoints son mucho más visibles en la interfaz de TestFlight y también en la herramienta de analíticas FlightPath (integrada con TestFlight), así que se me ocurrió que podían servirme como indicadores de asserts disparados.
A los checkpoints de tipo NSAssert los nombro siempre con el prefijo ASSERTION. Por ejemplo ASSERTION_NON_PARSEABLE_ITEM_DATA_RECEIVED.

Using:
Alog(@"ASSERTION_NON_PARSEABLE_ITEM_DATA_RECEIVED");
.. you get a checkpoint entry on your TestFlight Dashboard !!!

// #define NS_BLOCK_ASSERTIONS turns off assertions. Try putting NS_BLOCK_ASSERTIONS into the preprocessor macros of your target or even project (for the release configuration only): Or put #define NS_BLOCK_ASSERTIONS into the prefix (.pch) header before the #import <Cocoa/Cocoa.h> or #import <Foundation/Foundation.h> lines.
*/

/*
#ifdef DEBUG
I normally run my code in one of two modes. Either I am writing and testing the code or I am compiling it to hand over to QA, a user or Apple (btw I consider all three of those to be synonymous when it comes to builds). Therefore the first line is a switch to see if we are in debug mode. I set this value in the build settings of my project. If you look under the “Preprocessor Macros” section you can set the DEBUG definition there.
#define DLog(...)
This is the most used macro I have in my Prefix.pch file. This is simply NSLog as we know it and love it. However I automatically prepend the included macro __PRETTY_FUNCTION__ so that any log statement that comes out will declare where it is being called from. Personally I hate having to track down which “Fix Me” just spit out to the Console.
The nice thing about DLog over NSLog is that in the other branch this is a no-op that will be removed by the compiler. Therefore when I do a client build they won’t see the debug statements nor will their build be slowed down by any potential conditional logic around the debug statements.
#define ALog(...)
While I do not use this one very often I do like this one an awful lot. When I am in DEBUG mode it will throw an NSAssertion when it gets hit. This is similar to a common line of code that I see:

NSAssert(NO, @"It failed");
or if you want to see the variables:

NSAssert2(NO, @"It failed. Value1: %i Value2: %i", value1, value2);

My version does not have the condition before hand and can take any number of parameters.

ALog(@"It failed. Value1: %i Value2: %i", value1, value2);

In addition, when the DEBUG flag is not set, this assertion turns into a NSLog which remains visible. This allows me to have “This will never happen” calls in my code that will explode when I hit them but will be more polite if a user hits them but not so polite that I am left wondering what happened. They won’t intentionally crash the application but they will leave a fingerprint in the output from the application so that I can discover what happened.
NS_BLOCK_ASSERTIONS
I am of the school of thought that believes you should never throw an assertion in production code. If your code cannot handle that part of your app being hit and survive in some form or another then it is not production ready. Simple as that. Therefore I turn them off in production builds.
However, some other people who write libraries that I depend upon also feel this way. Therefore I need to check to see if it is already defined so that I can avoid a warning about resetting it. Since I have warnings set as errors in my code this is needed.
#define ZAssert(condition, ...)
The final gem in this collection is ZAssert. This is my personal favorite and it lets me clean up my code very nicely. First, ZAssert is a condition check. If you pass the check nothing happens. If you fail the check, bad things happen. This is just like NSAssert except for one big difference. When you turn off assertions, NSAssert goes away completely. This is not what I want to happen in my code. Instead, when assertions are turned off, I want a failure of this check to turn into an NSLog. That is what ZAssert does for us. In this way, we can clean up our code very nicely. Picture this very common block of code:

NSError *error = nil;
 
if (![managedObjectContext save:&error]) {
  NSLog(@"My save failed: %@\n%@", [error localizedDescription], [error userInfo]);
  abort();
}

That is a LOT of code just to perform a save! Blocks of code like this are very common in Objective-C. Unfortunately we can’t roll this up into a NSAssert because the entire line of code will disappear when we turn them off.
With ZAssert it gets a lot cleaner:

NSError *error = nil;
ZAssert([managedObjectContext save:&error], @"My save failed: %@\n%@", [error localizedDescription], [error userInfo]);
Because ZAssert survives when NS_BLOCK_ASSERTIONS is set and simply mutates, we can inline the save directly and make the code a lot easier to read.

Wrap Up
I am sure this code will evolve. When it has changed significantly I will do an updated post. If anyone else has some nice tips for the Prefix.pch then please share them as we all benefit.
*/