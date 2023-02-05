// Groove connector L90

//target_obj = "silver_only";

translate([0, -(10.2/2-1.5*2+3*2), 0]) {

    if (is_undef(target_obj) || (target_obj == "white_only"))
    color("White")
    difference() {
        difference() {
            cube([8, 10.2, 5.2]);
            
            translate([1.5-100, -50, 5.2-0.75])
            cube([100, 100, 100]);
            
            translate([-50, 2, 5.2-0.75])
            cube([100, 10.2 - 2*2, 100]);
        };

        translate([0.5, 0.5, 0.5])
        difference() {
            cube([50, 10.2-1, 5.2-1]);
            
            translate([1.5-100, -50, 5.2-0.75-1])
            cube([100, 100, 100]);
            
            translate([-50, 2-1, 5.2-0.75-1])
            cube([100, 10.2 - 2*2 + 1, 100]);
        };
        
        translate([4.75, 2.25, 1])
        cube([50, 10.2 - 2.25*2, 50]);
        
        translate([8.0-1.1, 1.5, -50+1])
        cube([50, 10.2 - 1.5*2, 50]);
    };

    if (is_undef(target_obj) || (target_obj == "silver_only"))
    color("Silver")
    translate([0, 0, 0, 0]) {
        for (a = [0:3]) {
            translate([(8-2)/2, 10.2/2-1.5*2+2*a, 2])
            cube([8-2-0.25, 0.5, 0.5], center = true);
            
            translate([0, 10.2/2-1.5*2+2*a, 0])
            cube([0.5, 0.5, 4], center = true);
        }
    }
}
