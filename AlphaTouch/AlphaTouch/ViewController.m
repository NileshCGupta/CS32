//
//  ViewController.m
//  AlphaTouch
//
//  Created by Nilesh Gupta on 11/9/15.
//  Copyright © 2015 Nilesh Gupta. All rights reserved.
//

#import "ViewController.h"

@interface ViewController ()

@end

@implementation ViewController

- (void)didReceiveMemoryWarning {
	[super didReceiveMemoryWarning];
	// Dispose of any resources that can be recreated.
}

- (void) viewDidLoad {
	[super viewDidLoad];
	self.view.backgroundColor = [UIColor greenColor];
}

- (void) loadView {
	CGRect viewRect = [[UIScreen mainScreen] bounds];
	UIView *view = [[UIView alloc] initWithFrame:viewRect];
	self.view = view;
}

@end
