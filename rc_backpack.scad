box = [40,75,18];
walls = 1;
union() {
	difference() {
		cube(box,center=true);
		translate([0,0,walls]) cube([box[0]-walls,box[1]-walls,box[2]],center=true);
		translate([0,box[1]/2-walls,-3])rotate([0,90,90])cylinder(r=3.5,h=10);
		translate([box[0]/2-walls,5,3])rotate([0,90,0])cylinder(r=3,h=10);
		translate([0,0,box[2]/2-walls/2]) lid();
	}
	translate([-box[0]/2,box[1]/2-10,-box[2]/2+walls])cube([10,10,2]);
	translate([box[0]/2-10,box[1]/2-10,-box[2]/2+walls])cube([10,10,2]);
	translate([box[0]/2-10,-box[1]/2,-box[2]/2+walls])cube([10,10,2]);
	translate([-box[0]/2,-box[1]/2,-box[2]/2+walls])cube([10,10,2]);
}

translate([box[0]+20,0,-box[2]/2+walls/2]) lid();

module lid() {
	difference() {
		cube([box[0],box[1],walls],center=true);
		translate([-box[0]/2+walls/2,0,0])cube([walls,10,walls],center=true);
		translate([box[0]/2-walls/2,0,0])cube([walls,10,walls],center=true);
		translate([0,-box[1]/2+walls/2,0])cube([10,walls,walls],center=true);
		translate([0,box[1]/2-walls/2,0])cube([10,walls,walls],center=true);
	}
}