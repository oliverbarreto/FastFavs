//
//  FFFFavsMainDeatailVCViewController.m
//  FastFavs
//
//  Created by David Oliver Barreto Rodríguez on 27/12/13.
//  Copyright (c) 2013 David Oliver Barreto Rodríguez. All rights reserved.
//

#import "DOBRFastFavsMainDetailCollectionViewVC.h"
#import "DOBRFastFavsDetailImageVC.h"
#import "DOBRFastFavCollectionViewCell.h"
#import "UIImage+RoundedCorner.h"
#import "UIImage+Resize.h"
#import "DOBRFastFavSectionHeader.h"


#pragma mark Details to Polish

TODO("Need to change the the label below each image ... center text in relation to image");
TODO("add time and date to header section");



@interface DOBRFastFavsMainDetailCollectionViewVC ()

// Model for FastFavs
@property (nonatomic, strong) NSMutableArray * favsGroups;
@property (nonatomic, strong) NSMutableArray * favs;
@property (nonatomic, strong) NSMutableArray * favsImages;

// Only needed if performing custom animation for hiding status bar on a per controller basis
@property BOOL shouldBeHidingStatusBar;
@end

@implementation DOBRFastFavsMainDetailCollectionViewVC



#pragma mark StatusBar Apperance Delegate Methods
-(UIStatusBarStyle)preferredStatusBarStyle {
    return UIStatusBarStyleLightContent;
}

-(BOOL)prefersStatusBarHidden {
    return self.shouldBeHidingStatusBar;
}

- (UIStatusBarAnimation)preferredStatusBarUpdateAnimation {
    return UIStatusBarAnimationSlide; // UIStatusBarAnimationFade or UIStatusBarAnimationNone;
}

/*
#pragma mark Autorotation
- (void)willAnimateRotationToInterfaceOrientation:(UIInterfaceOrientation)toInterfaceOrientation
                                         duration:(NSTimeInterval)duration {

    // If the orientation is rotating to Portrait mode...
    if (UIInterfaceOrientationIsPortrait(toInterfaceOrientation)) {

        // Create a new FlowLayout instance and invalidate the previous one to set the new scrolling VERTICAL FlowLayout
        UICollectionViewFlowLayout *myLayout =
        [[UICollectionViewFlowLayout alloc] init];
        
        myLayout.scrollDirection = UICollectionViewScrollDirectionVertical;
        [self.collectionView setCollectionViewLayout:myLayout animated:YES];

    // If the orientation is rotating to Landscape mode...
    } else {
        // Create a new FlowLayout instance and invalidate the previous one to set the new scrolling HORIZONTAL FlowLayout
        UICollectionViewFlowLayout *myLayout =
        [[UICollectionViewFlowLayout alloc] init];
        
        myLayout.scrollDirection = UICollectionViewScrollDirectionHorizontal;
        [self.collectionView setCollectionViewLayout:myLayout animated:YES];
        
    }
}
*/

#pragma mark View Life Cycle
- (id)initWithNibName:(NSString *)nibNameOrNil bundle:(NSBundle *)nibBundleOrNil
{
    self = [super initWithNibName:nibNameOrNil bundle:nibBundleOrNil];
    if (self) {
        // Custom initialization
    }
    return self;
}

- (void)viewDidLoad
{
    [super viewDidLoad];
	// Do any additional setup after loading the view.
    
    // Set VC Extended Layout to none
//    self.edgesForExtendedLayout = UIRectEdgeNone;
//    self.edgesForExtendedLayout = UIRectEdgeAll;
//    self.automaticallyAdjustsScrollViewInsets = YES;
    
    // Load Dummy Data
    [self loadDummyData];

    // Create Content Inset for Fixing the Header SEction Spacign from top
    self.collectionView.contentInset = UIEdgeInsetsMake(MAGIC_NUMBER(15), 0, 0, 0);

}


// Hide the status bar with a delayed animation when the VS gets shown on screen
-(void) viewDidAppear:(BOOL)animated {
    self.shouldBeHidingStatusBar = YES;
    [self performSelector:(@selector(animateStatusBar)) withObject:nil afterDelay:0.5];
}

-(void)animateStatusBar {
    [UIView animateWithDuration:0.5 animations:^{
        [self setNeedsStatusBarAppearanceUpdate];
    }];

}

- (void)didReceiveMemoryWarning
{
    [super didReceiveMemoryWarning];
    // Dispose of any resources that can be recreated.
}

#pragma mark Data Loading

-(void) loadDummyData {

    DDLogInfo(@"Loading Data");
    // Load Dummy Data at start up...
    
    // Groups
    self.favsGroups = [@[@"Family",
                         @"Work",
                         @"Friends"]
                       mutableCopy];

    // Persons' Names
    self.favs = [@[@"Oliver Barreto", @"Ana Acosta", @"Innovation Guy",
                   @"Raimon", @"Rosa Mary", @"Fernando Pérez",
                   @"JJuan", @"Gara Alom", @"Javier Herrera",
                   @"Miguel Herrera", @"María Duarte", @"Heidi", @"Sonia Acosta", @"Mima",
                   @"Oliver Barreto", @"Ana Acosta", @"Innovation Guy",
                   @"Raimon", @"Rosa Mary", @"Fernando Pérez",
                   @"JJuan", @"Gara Alom", @"Javier Herrera",
                   @"Miguel Herrera", @"María Duarte", @"Heidi", @"Sonia Acosta", @"Mima"]
                 mutableCopy];
    // Persons' Images
    self.favsImages = [@[@"Oliver.jpg", @"ARAL.jpg", @"OliverInnovation.jpg",
                         @"Raimon.jpg", @"RosaMary.jpg", @"FernandoPerez.jpg",
                         @"JJuan.jpg", @"GaraAlom.jpg", @"JavierHerrera.jpg",
                         @"MiguelHerrera.jpg", @"MariaDuarte.jpg", @"Heidi.jpg", @"SoniaAcosta.jpg", @"Mima.jpeg",
                         @"Oliver.jpg", @"ARAL.jpg", @"OliverInnovation.jpg",
                         @"Raimon.jpg", @"RosaMary.jpg", @"FernandoPerez.jpg",
                         @"JJuan.jpg", @"GaraAlom.jpg", @"JavierHerrera.jpg",
                         @"MiguelHerrera.jpg", @"MariaDuarte.jpg", @"Heidi.jpg", @"SoniaAcosta.jpg", @"Mima.jpeg"]
                       mutableCopy];
    
    DDLogInfo(@"Data has been loaded");
    
}


#pragma mark UICollectionView Protocol Methods
-(NSInteger)numberOfSectionsInCollectionView:(UICollectionView *)collectionView {
    return 1;
}

- (NSInteger)collectionView:(UICollectionView *)collectionView numberOfItemsInSection:(NSInteger)section {
    return self.favs.count;
}


- (UICollectionViewCell *)collectionView:(UICollectionView *)collectionView cellForItemAtIndexPath:(NSIndexPath *)indexPath {
    static NSString *identifier = @"FastFavCell";
    
    DOBRFastFavCollectionViewCell *cell = [collectionView dequeueReusableCellWithReuseIdentifier:identifier forIndexPath:indexPath];
    
   
    // Add Rounded Image 50%
    UIImage *tmpimage = [UIImage imageNamed:[self.favsImages objectAtIndex:indexPath.row]];
    UIImage *roundedimageforcell  = [tmpimage thumbnailImage:MAGIC_NUMBER(70) transparentBorder:MAGIC_NUMBER(5) cornerRadius:MAGIC_NUMBER(70/2) interpolationQuality:1];
    UIImageView * tmpImageView = [[UIImageView alloc] initWithImage:roundedimageforcell];
    

    // Add Shadow sublayer
    [cell.fastfavcellView.layer addSublayer:[self createRoundedShapeBackgroundLayerWithRadius:tmpImageView.bounds]];

    
    // Assign the image to the cell imageview
    [cell.fastfavcellView addSubview:tmpImageView];

    
    // Add Name
    if (cell.fastfavcellFullNameLabel == nil) {
        DDLogError(@"No label created");
    } else {
        DDLogInfo(@"label created for cell");
    }
    
//    (cell.fastfavcellFullNameLabel == nil) ? NSLog(@"No label created") : NSLog(@"label created for cell");
    cell.fastfavcellFullNameLabel.text = [self.favs objectAtIndex:indexPath.row];
    DDLogInfo(@"Label set to %@", [self.favs objectAtIndex:indexPath.row]);

    // Custom Background ImageView
    //cell.backgroundView = [[UIImageView alloc] initWithImage:[UIImage imageNamed:@"photo-frame.png"]];

    return cell;
}


#pragma mark UICollectionViewDelegateFlowLayout

-(CGSize)collectionView:(UICollectionView *)collectionView layout:(UICollectionViewLayout *)collectionViewLayout sizeForItemAtIndexPath:(NSIndexPath *)indexPath
{
    //FastFavs Cells are 110x110 points
    CGSize fastfavcellSize = CGSizeMake(MAGIC_NUMBER(100), MAGIC_NUMBER(115));
    
    return fastfavcellSize;
}


-(UICollectionReusableView *)collectionView:(UICollectionView *)collectionView viewForSupplementaryElementOfKind:(NSString *)kind atIndexPath:(NSIndexPath *)indexPath
{
    DOBRFastFavSectionHeader * fastfavcellSetionHeader = nil;
    
    if ([kind isEqual:UICollectionElementKindSectionHeader])
    {
        fastfavcellSetionHeader = [collectionView dequeueReusableSupplementaryViewOfKind:kind
                                                    withReuseIdentifier:@"FastFavSectionHeader"
                                                           forIndexPath:indexPath];

        // Configure Section Label and set text to Group Name
        fastfavcellSetionHeader.fastfavSectionHeaderLabel.font = [UIFont fontWithName:@"HelveticaNeue-CondensedBlack" size:60.0];
        fastfavcellSetionHeader.fastfavSectionHeaderLabel.shadowColor = [UIColor colorWithRed:0.0 green:0.0 blue:0.0 alpha:0.8];
        fastfavcellSetionHeader.fastfavSectionHeaderLabel.shadowOffset = CGSizeMake(1, 1);

        fastfavcellSetionHeader.fastfavSectionHeaderLabel.text = self.favsGroups[0];
}
    
    return fastfavcellSetionHeader;
}

- (UIEdgeInsets)collectionView:(UICollectionView *)collectionView layout:(UICollectionViewLayout *)collectionViewLayout insetForSectionAtIndex:(NSInteger)section
{
    // Space the collection view from the top
    return UIEdgeInsetsMake(MAGIC_NUMBER(335), 0, 0, 0);

}

#pragma mark Prepare for Segue
- (void)prepareForSegue:(UIStoryboardSegue *)segue
                 sender:(id)sender {

    if ([segue.identifier isEqualToString:@"showFavPhoto"]) {

        
        NSArray *indexPaths = [self.collectionView indexPathsForSelectedItems];
        DOBRFastFavsDetailImageVC *destViewController = segue.destinationViewController;
        
        // Select the first item for ingle selection
        NSIndexPath *indexPath = [indexPaths objectAtIndex:0];
        
        // Initialize destination VC
        destViewController.favImageName = [self.favsImages objectAtIndex:indexPath.row];
        destViewController.navigationItem.title = [self.favs objectAtIndex:indexPath.row];

        // Deselect cell
        [self.collectionView deselectItemAtIndexPath:indexPath animated:NO];
    }
}

#pragma mark Utility Methods
- (UIImage *) image:(UIImage *)image withRoundedCornersRadius:(float)radius
{
    // Begin a new image that will be the new image with the rounded corners
    UIGraphicsBeginImageContextWithOptions(image.size, NO, 0);
    
    // Add a clip before drawing anything, in the shape of an rounded rect
    CGRect rect = CGRectMake(0, 0, image.size.width, image.size.height);
    [[UIBezierPath bezierPathWithRoundedRect:rect cornerRadius:radius] addClip];
    
    // Draw your image
    [image drawInRect:rect];
    
    // Get the image, here setting the UIImageView image
    UIImage *roundedImage = UIGraphicsGetImageFromCurrentImageContext();
    
    // Lets forget about that we were drawing
    UIGraphicsEndImageContext();
    
    return roundedImage;
}


-(void)setShadowForView:(UIImageView *)originalView {
    
    // Get the current Center
    originalView.center = self.view.center;
    
    // make new layer to contain shadow and masked image
    CALayer* containerLayer = [CALayer layer];
    containerLayer.shadowColor = [UIColor blackColor].CGColor;
    containerLayer.shadowRadius = 10.f;
    containerLayer.shadowOffset = CGSizeMake(0.f, 5.f);
    containerLayer.shadowOpacity = 1.f;
   
    // add masked image layer into container layer so that it's shadowed
    [containerLayer addSublayer:originalView.layer];
    
    // add container including masked image and shadow into view
    [self.view.layer addSublayer:containerLayer];
    
    //shadow part
    originalView.layer.shadowColor = [UIColor blackColor].CGColor;
    originalView.layer.shadowOffset = CGSizeMake(0, 1);
    originalView.layer.shadowOpacity = 1;
    originalView.layer.shadowRadius = 1.0;
    originalView.clipsToBounds = NO;

    //white border part
    [originalView.layer setBorderColor: [[UIColor whiteColor] CGColor]];
    [originalView.layer setBorderWidth: 2.0];
}

-(CAShapeLayer *)createRoundedShapeBackgroundLayerWithRadius:(CGRect)rect {
    
    CAShapeLayer *layer = [[CAShapeLayer alloc] init];
    layer.path = [UIBezierPath bezierPathWithOvalInRect:rect].CGPath;
    layer.fillColor = [UIColor whiteColor].CGColor;
    layer.opacity = 0.8;

    return layer;
}

@end
