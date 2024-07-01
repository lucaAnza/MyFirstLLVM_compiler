define double @pow2(double %x, double %i) {
entry:
  %i2 = alloca double, align 8
  %x1 = alloca double, align 8
  store double %x, ptr %x1, align 8
  store double %i, ptr %i2, align 8
  %x3 = load double, ptr %x1, align 8
  %i4 = load double, ptr %i2, align 8
  %mulres = fmul double 2.000000e+00, %i4
  %lessIF = fcmp ult double %x3, %mulres
  br i1 %lessIF, label %true_BB, label %false_BB

true_BB:                                          ; preds = %entry
  %i5 = load double, ptr %i2, align 8
  br label %mergeBB

false_BB:                                         ; preds = %entry
  %x6 = load double, ptr %x1, align 8
  %i7 = load double, ptr %i2, align 8
  %mulres8 = fmul double 2.000000e+00, %i7
  %calltmp = call double @pow2(double %x6, double %mulres8)
  br label %mergeBB

mergeBB:                                          ; preds = %false_BB, %true_BB
  %0 = phi double [ %i5, %true_BB ], [ %calltmp, %false_BB ]
  ret double %0
}

define double @intpart(double %x, double %acc) {
entry:
  %y = alloca double, align 8
  %acc2 = alloca double, align 8
  %x1 = alloca double, align 8
  store double %x, ptr %x1, align 8
  store double %acc, ptr %acc2, align 8
  %x3 = load double, ptr %x1, align 8
  %lessIF = fcmp ult double %x3, 1.000000e+00
  br i1 %lessIF, label %true_BB, label %false_BB

true_BB:                                          ; preds = %entry
  br label %mergeBB

false_BB:                                         ; preds = %entry
  %x4 = load double, ptr %x1, align 8
  %calltmp = call double @pow2(double %x4, double 1.000000e+00)
  br label %mergeBB

mergeBB:                                          ; preds = %false_BB, %true_BB
  %0 = phi double [ 0.000000e+00, %true_BB ], [ %calltmp, %false_BB ]
  store double %0, ptr %y, align 8
  %y5 = load double, ptr %y, align 8
  %equalIF = fcmp ueq double %y5, 0.000000e+00
  br i1 %equalIF, label %true_BB6, label %false_BB7

true_BB6:                                         ; preds = %mergeBB
  %acc9 = load double, ptr %acc2, align 8
  br label %mergeBB8

false_BB7:                                        ; preds = %mergeBB
  %x10 = load double, ptr %x1, align 8
  %y11 = load double, ptr %y, align 8
  %subres = fsub double %x10, %y11
  %acc12 = load double, ptr %acc2, align 8
  %y13 = load double, ptr %y, align 8
  %addres = fadd double %acc12, %y13
  %calltmp14 = call double @intpart(double %subres, double %addres)
  br label %mergeBB8

mergeBB8:                                         ; preds = %false_BB7, %true_BB6
  %1 = phi double [ %acc9, %true_BB6 ], [ %calltmp14, %false_BB7 ]
  ret double %1
}

define double @floor(double %x) {
entry:
  %x1 = alloca double, align 8
  store double %x, ptr %x1, align 8
  %x2 = load double, ptr %x1, align 8
  %calltmp = call double @intpart(double %x2, double 0.000000e+00)
  ret double %calltmp
}

