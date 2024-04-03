// Fill out your copyright notice in the Description page of Project Settings.


#include "UnitAnim.h"

void UUnitAnim::Animate(AUnitCharacter* Character)
{
	Speed = Character->GetVelocity().Size();

	//Set IsWalking based on Speed
	Speed > 0 ? IsWalking = true : IsWalking = false;

}
