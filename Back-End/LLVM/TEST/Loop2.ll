; ModuleID = 'TEST/source_c_files/Loop2.c'
source_filename = "TEST/source_c_files/Loop2.c"
target datalayout = "e-m:e-p270:32:32-p271:32:32-p272:64:64-i64:64-f80:128-n8:16:32:64-S128"
target triple = "x86_64-unknown-linux-gnu"

@.str = private unnamed_addr constant [4 x i8] c"%d \00", align 1

; Function Attrs: noinline nounwind optnone uwtable
define dso_local i32 @main() #0 {
  %1 = alloca i32, align 4
  %2 = alloca i32, align 4
  %3 = alloca i32, align 4
  %4 = alloca i32, align 4
  %5 = alloca i32, align 4
  %6 = alloca i32, align 4
  %7 = alloca i32, align 4
  %8 = alloca i32, align 4
  store i32 0, ptr %1, align 4
  store i32 3, ptr %6, align 4
  store i32 6, ptr %7, align 4
  store i32 0, ptr %2, align 4
  br label %9

9:                                                ; preds = %12, %0
  %10 = load i32, ptr %2, align 4
  %11 = icmp slt i32 %10, 10
  br i1 %11, label %12, label %15

12:                                               ; preds = %9
  %13 = load i32, ptr %2, align 4
  %14 = add nsw i32 %13, 1
  store i32 %14, ptr %2, align 4
  br label %9, !llvm.loop !6

15:                                               ; preds = %9
  store i32 20, ptr %3, align 4
  br label %16

16:                                               ; preds = %19, %15
  %17 = load i32, ptr %3, align 4
  %18 = icmp sge i32 %17, 10
  br i1 %18, label %19, label %22

19:                                               ; preds = %16
  %20 = load i32, ptr %3, align 4
  %21 = sub nsw i32 %20, 2
  store i32 %21, ptr %3, align 4
  br label %16, !llvm.loop !8

22:                                               ; preds = %16
  store i32 0, ptr %4, align 4
  store i32 0, ptr %5, align 4
  br label %23

23:                                               ; preds = %33, %22
  %24 = load i32, ptr %5, align 4
  %25 = icmp slt i32 %24, 5
  br i1 %25, label %26, label %36

26:                                               ; preds = %23
  %27 = load i32, ptr %4, align 4
  %28 = srem i32 %27, 2
  %29 = icmp eq i32 %28, 0
  br i1 %29, label %30, label %33

30:                                               ; preds = %26
  %31 = load i32, ptr %5, align 4
  %32 = add nsw i32 %31, 1
  store i32 %32, ptr %5, align 4
  br label %33

33:                                               ; preds = %30, %26
  %34 = load i32, ptr %4, align 4
  %35 = add nsw i32 %34, 1
  store i32 %35, ptr %4, align 4
  br label %23, !llvm.loop !9

36:                                               ; preds = %23
  store i32 1, ptr %2, align 4
  br label %37

37:                                               ; preds = %51, %36
  %38 = load i32, ptr %2, align 4
  %39 = icmp sle i32 %38, 100
  br i1 %39, label %40, label %54

40:                                               ; preds = %37
  %41 = load i32, ptr %2, align 4
  %42 = srem i32 %41, 3
  %43 = icmp eq i32 %42, 0
  br i1 %43, label %44, label %51

44:                                               ; preds = %40
  %45 = load i32, ptr %2, align 4
  %46 = srem i32 %45, 5
  %47 = icmp eq i32 %46, 0
  br i1 %47, label %48, label %51

48:                                               ; preds = %44
  %49 = load i32, ptr %7, align 4
  %50 = add nsw i32 %49, 4
  store i32 %50, ptr %7, align 4
  br label %51

51:                                               ; preds = %48, %44, %40
  %52 = load i32, ptr %2, align 4
  %53 = add nsw i32 %52, 1
  store i32 %53, ptr %2, align 4
  br label %37, !llvm.loop !10

54:                                               ; preds = %37
  store i32 1, ptr %3, align 4
  br label %55

55:                                               ; preds = %65, %54
  %56 = load i32, ptr %3, align 4
  %57 = icmp sle i32 %56, 20
  br i1 %57, label %58, label %68

58:                                               ; preds = %55
  %59 = load i32, ptr %3, align 4
  %60 = srem i32 %59, 2
  %61 = icmp ne i32 %60, 0
  br i1 %61, label %62, label %65

62:                                               ; preds = %58
  %63 = load i32, ptr %6, align 4
  %64 = sub nsw i32 %63, 3
  store i32 %64, ptr %6, align 4
  br label %65

65:                                               ; preds = %62, %58
  %66 = load i32, ptr %3, align 4
  %67 = add nsw i32 %66, 1
  store i32 %67, ptr %3, align 4
  br label %55, !llvm.loop !11

68:                                               ; preds = %55
  store i32 0, ptr %2, align 4
  br label %69

69:                                               ; preds = %76, %68
  %70 = load i32, ptr %2, align 4
  %71 = icmp slt i32 %70, 10
  br i1 %71, label %72, label %79

72:                                               ; preds = %69
  %73 = load i32, ptr %7, align 4
  %74 = load i32, ptr %6, align 4
  %75 = add nsw i32 %73, %74
  store i32 %75, ptr %7, align 4
  br label %76

76:                                               ; preds = %72
  %77 = load i32, ptr %2, align 4
  %78 = add nsw i32 %77, 1
  store i32 %78, ptr %2, align 4
  br label %69, !llvm.loop !12

79:                                               ; preds = %69
  store i32 1, ptr %3, align 4
  br label %80

80:                                               ; preds = %88, %79
  %81 = load i32, ptr %3, align 4
  %82 = icmp sle i32 %81, 10
  br i1 %82, label %83, label %91

83:                                               ; preds = %80
  %84 = load i32, ptr %3, align 4
  %85 = load i32, ptr %3, align 4
  %86 = mul nsw i32 %84, %85
  %87 = call i32 (ptr, ...) @printf(ptr noundef @.str, i32 noundef %86)
  br label %88

88:                                               ; preds = %83
  %89 = load i32, ptr %3, align 4
  %90 = add nsw i32 %89, 1
  store i32 %90, ptr %3, align 4
  br label %80, !llvm.loop !13

91:                                               ; preds = %80
  store i32 3, ptr %8, align 4
  store i32 1, ptr %4, align 4
  br label %92

92:                                               ; preds = %106, %91
  %93 = load i32, ptr %4, align 4
  %94 = icmp sle i32 %93, 5
  br i1 %94, label %95, label %109

95:                                               ; preds = %92
  store i32 1, ptr %3, align 4
  br label %96

96:                                               ; preds = %102, %95
  %97 = load i32, ptr %3, align 4
  %98 = icmp sle i32 %97, 10
  br i1 %98, label %99, label %105

99:                                               ; preds = %96
  %100 = load i32, ptr %8, align 4
  %101 = add nsw i32 %100, 1
  store i32 %101, ptr %8, align 4
  br label %102

102:                                              ; preds = %99
  %103 = load i32, ptr %3, align 4
  %104 = add nsw i32 %103, 1
  store i32 %104, ptr %3, align 4
  br label %96, !llvm.loop !14

105:                                              ; preds = %96
  br label %106

106:                                              ; preds = %105
  %107 = load i32, ptr %4, align 4
  %108 = add nsw i32 %107, 1
  store i32 %108, ptr %4, align 4
  br label %92, !llvm.loop !15

109:                                              ; preds = %92
  ret i32 0
}

declare i32 @printf(ptr noundef, ...) #1

attributes #0 = { noinline nounwind optnone uwtable "frame-pointer"="all" "min-legal-vector-width"="0" "no-trapping-math"="true" "stack-protector-buffer-size"="8" "target-cpu"="x86-64" "target-features"="+cmov,+cx8,+fxsr,+mmx,+sse,+sse2,+x87" "tune-cpu"="generic" }
attributes #1 = { "frame-pointer"="all" "no-trapping-math"="true" "stack-protector-buffer-size"="8" "target-cpu"="x86-64" "target-features"="+cmov,+cx8,+fxsr,+mmx,+sse,+sse2,+x87" "tune-cpu"="generic" }

!llvm.module.flags = !{!0, !1, !2, !3, !4}
!llvm.ident = !{!5}

!0 = !{i32 1, !"wchar_size", i32 4}
!1 = !{i32 8, !"PIC Level", i32 2}
!2 = !{i32 7, !"PIE Level", i32 2}
!3 = !{i32 7, !"uwtable", i32 2}
!4 = !{i32 7, !"frame-pointer", i32 2}
!5 = !{!"clang version 17.0.6 (https://github.com/lucaAnza/MyFirstLLVM_compiler.git 101cdc04a9f3388803c4019979dede8170a461ae)"}
!6 = distinct !{!6, !7}
!7 = !{!"llvm.loop.mustprogress"}
!8 = distinct !{!8, !7}
!9 = distinct !{!9, !7}
!10 = distinct !{!10, !7}
!11 = distinct !{!11, !7}
!12 = distinct !{!12, !7}
!13 = distinct !{!13, !7}
!14 = distinct !{!14, !7}
!15 = distinct !{!15, !7}
