// Copyright Csaba Molnar, Daniel Butum. All Rights Reserved.
#pragma once

#include "CoreMinimal.h"

#include "DlgEvent.h"
#include "DlgCondition.h"
#include "DlgTextArgument.h"

//////////////////////////////////////////////////////////////////////////
// FDialogueESearchUtilities

class UDlgDialogue;
class UDialogueGraphNode;
struct FDlgNode;
class UEdGraph;
class UDialogueGraphNode_Base;
class UDialogueGraphNode_Edge;

// Represents the found result of the search functions.
struct FDialogueSearchFoundResult
{
private:
	typedef FDialogueSearchFoundResult Self;

public:
	static TSharedPtr<FDialogueSearchFoundResult> Make() { return MakeShared<Self>(); }

public:
	// Nodes that satisfy the search result.
	TArray<TWeakObjectPtr<const UDialogueGraphNode>> GraphNodes;

	// Edges that satisfy the search result.
	TArray<TWeakObjectPtr<const UDialogueGraphNode_Edge>> EdgeNodes;
};

/**
 * Utilities for search.
 * @brief The FDialogueSearchUtilities class
 */
class FDialogueSearchUtilities
{
public:

	/**
	 * Gets all the graph nodes that contain the specified EventName (of the EventType Event)
	 */
	static TSharedPtr<FDialogueSearchFoundResult> GetGraphNodesForEventEventName(FName EventName, const UDlgDialogue* Dialogue);

	/**
	 * Gets all the graph nodes that contain the specified ConditionName (of the ConditionType EventCall)
	 * This contains both graph nodes and edges.
	 */
	static TSharedPtr<FDialogueSearchFoundResult> GetGraphNodesForConditionEventCallName(FName ConditionName, const UDlgDialogue* Dialogue);

	/**
	 * Gets all the graph nodes that contain the specified IntVariableName basic type.
	 * This contains both graph nodes and edges.
	 */
	static TSharedPtr<FDialogueSearchFoundResult> GetGraphNodesForIntVariableName(FName IntVariableName, const UDlgDialogue* Dialogue)
	{
		TSharedPtr<FDialogueSearchFoundResult> FoundResult = GetGraphNodesForVariablesOfNameAndType(
			IntVariableName,
			Dialogue,
			EDlgEventType::ModifyInt,
			EDlgConditionType::IntCall
		);
		GetGraphNodesForTextArgumentVariable(IntVariableName, Dialogue, EDlgTextArgumentType::DialogueInt, FoundResult);
		return FoundResult;
	}

	/**
	 * Gets all the graph nodes that contain the specified FloatVariableName basic type.
	 * This contains both graph nodes and edges.
	 */
	static TSharedPtr<FDialogueSearchFoundResult> GetGraphNodesForFloatVariableName(FName FloatVariableName, const UDlgDialogue* Dialogue)
	{
		TSharedPtr<FDialogueSearchFoundResult> FoundResult = GetGraphNodesForVariablesOfNameAndType(
			FloatVariableName,
			Dialogue,
			EDlgEventType::ModifyFloat,
			EDlgConditionType::FloatCall
		);
		GetGraphNodesForTextArgumentVariable(FloatVariableName, Dialogue, EDlgTextArgumentType::DialogueInt, FoundResult);
		return FoundResult;
	}

	/**
	 * Gets all the graph nodes that contain the specified BoolVariableName basic type.
	 * This contains both graph nodes and edges.
	 */
	static TSharedPtr<FDialogueSearchFoundResult> GetGraphNodesForBoolVariableName(FName BoolVariableName, const UDlgDialogue* Dialogue)
	{
		return GetGraphNodesForVariablesOfNameAndType(
			BoolVariableName,
			Dialogue,
			EDlgEventType::ModifyBool,
			EDlgConditionType::BoolCall
		);
	}

	/**
	 * Gets all the graph nodes that contain the specified FNameVariableName basic type.
	 * This contains both graph nodes and edges.
	 */
	static TSharedPtr<FDialogueSearchFoundResult> GetGraphNodesForFNameVariableName(FName FNameVariableName, const UDlgDialogue* Dialogue)
	{
		return GetGraphNodesForVariablesOfNameAndType(
			FNameVariableName,
			Dialogue,
			EDlgEventType::ModifyName,
			EDlgConditionType::NameCall
		);
	}

	/**
	 * Gets all the graph nodes that contain the specified IntVariableName from the UClass.
	 * This contains both graph nodes and edges.
	 */
	static TSharedPtr<FDialogueSearchFoundResult> GetGraphNodesForClassIntVariableName(FName IntVariableName, const UDlgDialogue* Dialogue)
	{
		TSharedPtr<FDialogueSearchFoundResult> FoundResult = GetGraphNodesForVariablesOfNameAndType(
			IntVariableName,
			Dialogue,
			EDlgEventType::ModifyClassIntVariable,
			EDlgConditionType::ClassIntVariable
		);
		GetGraphNodesForTextArgumentVariable(IntVariableName, Dialogue, EDlgTextArgumentType::ClassInt, FoundResult);
		return FoundResult;
	}

	/**
	 * Gets all the graph nodes that contain the specified FloatVariableName from the UClass.
	 * This contains both graph nodes and edges.
	 */
	static TSharedPtr<FDialogueSearchFoundResult> GetGraphNodesForClassFloatVariableName(FName FloatVariableName, const UDlgDialogue* Dialogue)
	{

		TSharedPtr<FDialogueSearchFoundResult> FoundResult = GetGraphNodesForVariablesOfNameAndType(
			FloatVariableName,
			Dialogue,
			EDlgEventType::ModifyClassFloatVariable,
			EDlgConditionType::FloatVariable
		);
		GetGraphNodesForTextArgumentVariable(FloatVariableName, Dialogue, EDlgTextArgumentType::ClassFloat, FoundResult);
		return FoundResult;
	}

	/**
	 * Gets all the graph nodes that contain the specified BoolVariableName from the UClass.
	 * This contains both graph nodes and edges.
	 */
	static TSharedPtr<FDialogueSearchFoundResult> GetGraphNodesForClassBoolVariableName(FName BoolVariableName, const UDlgDialogue* Dialogue)
	{
		return GetGraphNodesForVariablesOfNameAndType(
			BoolVariableName,
			Dialogue,
			EDlgEventType::ModifyClassBoolVariable,
			EDlgConditionType::ClassBoolVariable
		);
	}

	/**
	 * Gets all the graph nodes that contain the specified FNameVariableName from the UClass.
	 * This contains both graph nodes and edges.
	 */
	static TSharedPtr<FDialogueSearchFoundResult> GetGraphNodesForClassFNameVariableName(FName FNameVariableName, const UDlgDialogue* Dialogue)
	{
		return GetGraphNodesForVariablesOfNameAndType(
			FNameVariableName,
			Dialogue,
			EDlgEventType::ModifyClassNameVariable,
			EDlgConditionType::ClassNameVariable
		);
	}

	/**
	 * Gets all the graph nodes that contain the specified FNameVariableName from the UClass.
	 * This contains both graph nodes and edges.
	 */
	static TSharedPtr<FDialogueSearchFoundResult> GetGraphNodesForClassFTextVariableName(FName FTextVariableName, const UDlgDialogue* Dialogue)
	{
		TSharedPtr<FDialogueSearchFoundResult> FoundResult = FDialogueSearchFoundResult::Make();
		GetGraphNodesForTextArgumentVariable(FTextVariableName, Dialogue, EDlgTextArgumentType::ClassText, FoundResult);
		return FoundResult;
	}

	/** Does Conditions contain the ConditionName (of type ConditionType)? */
	static bool IsConditionInArray(
		FName ConditionName,
		EDlgConditionType ConditionType,
		const TArray<FDlgCondition>& Conditions
	)
	{
		for (const FDlgCondition& Condition : Conditions)
		{
			if (Condition.ConditionType == ConditionType &&
				(Condition.CallbackName == ConditionName || Condition.OtherVariableName == ConditionName))
			{
				return true;
			}
		}
		return false;
	}

	/** Does Events contain the EventName (of type EventType)? */
	static bool IsEventInArray(FName EventName, EDlgEventType EventType, const TArray<FDlgEvent>& Events)
	{
		for (const FDlgEvent& Event : Events)
		{
			if (Event.EventType == EventType && Event.EventName == EventName)
			{
				return true;
			}
		}
		return false;
	}

	/** Does Events contain the EventName (of type EventType)? */
	static bool IsTextArgumentInArray(FName TextArgumentName, EDlgTextArgumentType TextArgumentType, const TArray<FDlgTextArgument>& TextArguments)
	{
		for (const FDlgTextArgument& TextArgument : TextArguments)
		{
			if (TextArgument.Type == TextArgumentType && TextArgument.VariableName == TextArgumentName)
			{
				return true;
			}
		}
		return false;
	}

private:
	static TSharedPtr<FDialogueSearchFoundResult> GetGraphNodesForVariablesOfNameAndType(
		FName VariableName,
		const UDlgDialogue* Dialogue,
		EDlgEventType EventType,
		EDlgConditionType ConditionType
	);

	static void GetGraphNodesForTextArgumentVariable(
		FName VariableName,
		const UDlgDialogue* Dialogue,
		EDlgTextArgumentType ArgumentType,
		TSharedPtr<FDialogueSearchFoundResult>& FoundResult
	);
};
