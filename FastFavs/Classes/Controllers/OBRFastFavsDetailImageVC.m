//
//  FFFFavImageViewController.m
//  FastFavs
//
//  Created by David Oliver Barreto Rodríguez on 27/12/13.
//  Copyright (c) 2013 David Oliver Barreto Rodríguez. All rights reserved.
//

#import "OBRFastFavsDetailImageVC.h"

@interface OBRFastFavsDetailImageVC ()
@property (weak, nonatomic) IBOutlet UIImageView *favImageView;

- (IBAction)close:(UIBarButtonItem *)sender;

@end

@implementation OBRFastFavsDetailImageVC



#pragma mark StatusBar Apperance Delegate Methods
-(UIStatusBarStyle)preferredStatusBarStyle {
    return UIStatusBarStyleLightContent;
}

-(BOOL)prefersStatusBarHidden {
    return YES;
}

- (UIStatusBarAnimation)preferredStatusBarUpdateAnimation {
    return UIStatusBarAnimationSlide; // UIStatusBarAnimationFade or UIStatusBarAnimationNone;
}


#pragma mark Initializer
- (id)initWithNibName:(NSString *)nibNameOrNil bundle:(NSBundle *)nibBundleOrNil
{
    self = [super initWithNibName:nibNameOrNil bundle:nibBundleOrNil];
    if (self) {
        // Custom initialization
    }
    return self;
}


#pragma mark View Life Cycle

- (void)viewDidLoad
{
    [super viewDidLoad];
	// Do any additional setup after loading the view.
   
    //Load Image from name passed cell
    self.favImageView.image = [UIImage imageNamed:self.favImageName];
//    self.recipeImageView.image = [UIImage imageNamed:self.recipeImageName];

}

- (void)didReceiveMemoryWarning
{
    [super didReceiveMemoryWarning];
    // Dispose of any resources that can be recreated.
}



#pragma mark IBAction Methods
- (IBAction)close:(UIBarButtonItem *)sender {
    [self dismissViewControllerAnimated:YES completion:NULL];
}



@end
