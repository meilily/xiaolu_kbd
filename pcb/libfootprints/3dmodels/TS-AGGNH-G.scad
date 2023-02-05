// Switronic lndustrial Corp. TS-AGGNH-G (TS-AGGNH-xxxG-G)

//target_obj = "silver_only";

translate([6.5/2, -4.5/2, 0]) {
    
    if (is_undef(target_obj) || (target_obj == "white_only"))
    color("White")
    union() {
        translate([-10/2, -10/2, 4.75])
        cube([10, 10, 2.7]);
        translate([-8/2, -8/2-1/2, 0])
        cube([8, 1, 4.75+0.25]);
        translate([-8/2, +8/2-1/2, 0])
        cube([8, 1, 4.75+0.25]);
    };


    if (is_undef(target_obj) || target_obj == "green_only")
    color("Green")
    translate([-7.8/2, -7.8/2, 4.75+0.7])
    cube([7.8, 7.8, 2.7]);

    if (is_undef(target_obj) || target_obj == "black_only")
    color("Black")
    translate([-6.5/2, -7/2, 0])
    cube([6.5, 7, 4.75+0.25]);

    if (is_undef(target_obj) || target_obj == "silver_only")
    color("Silver")
    union() {
        translate([-0.3/2-6.5/2, -0.8/2-4.5/2, -3.6])
        cube([0.3, 0.8, 3.6+0.25]);
        translate([-0.3/2-6.5/2, -0.8/2+4.5/2, -3.6])
        cube([0.3, 0.8, 3.6+0.25]);
        translate([-0.3/2+6.5/2, -0.8/2-4.5/2, -3.6])
        cube([0.3, 0.8, 3.6+0.25]);
        translate([-0.3/2+6.5/2, -0.8/2+4.5/2, -3.6])
        cube([0.3, 0.8, 3.6+0.25]);
    };

}


