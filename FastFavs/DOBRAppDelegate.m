//
//  DOBRAppDelegate.m
//  FastFavs
//
//  Created by David Oliver Barreto Rodríguez on 07/01/14.
//  Copyright (c) 2014 David Oliver Barreto Rodríguez. All rights reserved.
//

#import "DOBRAppDelegate.h"

@implementation DOBRAppDelegate


#pragma mark Utility Methods

-(void)setupDevelopmentFramework
{
    // Send logs to Xcode console (DDTTYLogger) and Testfligh servers (TestFlightLogger)


    // TestFlight setup
//    [TestFlight takeOff:@"YOUR-APP-TOKEN-GOES-HERE"];
    
    // CocoaLumberjack setup
//    [DDLog addLogger:[TestFlightLogger sharedInstance]];
    [DDLog addLogger:[DDTTYLogger sharedInstance]];
    
    // DEBUG MODE: ddLogLevel = LOG_LEVEL_VERBOSE & RELEASE MODE: ddLogLevel = LOG_LEVEL_WARN in prefix.pch

    // SETUP Colors for CocoaLumberjack Dlogs... Now you can even change the color of a certain level
    [[DDTTYLogger sharedInstance] setColorsEnabled:YES];
    [[DDTTYLogger sharedInstance] setForegroundColor:[UIColor greenColor] backgroundColor:nil forFlag:LOG_FLAG_INFO];
    [[DDTTYLogger sharedInstance] setForegroundColor:[UIColor orangeColor] backgroundColor:nil forFlag:LOG_FLAG_WARN];
    [[DDTTYLogger sharedInstance] setForegroundColor:[UIColor redColor] backgroundColor:nil forFlag:LOG_FLAG_ERROR];
    [[DDTTYLogger sharedInstance] setForegroundColor:[UIColor whiteColor] backgroundColor:nil forFlag:LOG_LEVEL_VERBOSE];

}

- (BOOL)application:(UIApplication *)application didFinishLaunchingWithOptions:(NSDictionary *)launchOptions
{
    // Override point for customization after application launch.
    
    // setup CocoaLumberJack & other frameworks such as TestFlight, etc...
    [self setupDevelopmentFramework];
    
    return YES;
}
							
- (void)applicationWillResignActive:(UIApplication *)application
{
    // Sent when the application is about to move from active to inactive state. This can occur for certain types of temporary interruptions (such as an incoming phone call or SMS message) or when the user quits the application and it begins the transition to the background state.
    // Use this method to pause ongoing tasks, disable timers, and throttle down OpenGL ES frame rates. Games should use this method to pause the game.
}

- (void)applicationDidEnterBackground:(UIApplication *)application
{
    // Use this method to release shared resources, save user data, invalidate timers, and store enough application state information to restore your application to its current state in case it is terminated later. 
    // If your application supports background execution, this method is called instead of applicationWillTerminate: when the user quits.
}

- (void)applicationWillEnterForeground:(UIApplication *)application
{
    // Called as part of the transition from the background to the inactive state; here you can undo many of the changes made on entering the background.
}

- (void)applicationDidBecomeActive:(UIApplication *)application
{
    // Restart any tasks that were paused (or not yet started) while the application was inactive. If the application was previously in the background, optionally refresh the user interface.
}

- (void)applicationWillTerminate:(UIApplication *)application
{
    // Called when the application is about to terminate. Save data if appropriate. See also applicationDidEnterBackground:.
}

@end
