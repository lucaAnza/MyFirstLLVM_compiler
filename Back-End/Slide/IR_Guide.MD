# Compact IR-Guide

## Examples

### Ex1

``` text
define dso_local i32 @foo(i32 noundef %0, i32 noundef %1) #0 {
  %3 = add nsw i32 %1, 1
  %4 = mul nsw i32 %3, 2
  %5 = shl i32 %0, 1
  %6 = sdiv i32 %5, 4
  %7 = mul nsw i32 %4, %6
  ret i32 %7
}
```

## Function

Example1 : define dso_local i32 @foo(i32 noundef %0 , i32 noundef %1 )

- dso_local -> ha visibilità locale nel modulo corrente.
- i32 -> tipo di ritorno.
- @foo -> nome funzione.
- noundef -> gli argomenti non possono essere undefined

## Data type

- i32 -> Intero 32bit


## Operations

- mul
- add
- shl
- sdiv

## Operations - decorator

- nsw -> indica ci sarà overflow quando sarà eseguita l'operazione.

