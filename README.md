---

# Advanced Interaction System

Reusable interaction plugin for Unreal Engine.
Provides a modular, extensible C++ framework for interaction detection, focus events, instant and hold interactions, and optional advanced features.

---

## Overview

This plugin provides two levels of interaction components:

### Minimal System

* Interactable interface (`IInteractable`)
* Interactable component (`UInteractableComponent`)
* Interaction scanner (`UInteractionScannerComponent`)
* Optional `IInteractionSource` interface to define where traces originate

### Extended AAA System

* Priority-based interactables
* Hold-to-interact logic
* Continuous interactions
* Interaction phases (Started, Completed, Cancelled)
* Gameplay Tag support
* Advanced scanner with automatic update of hold progress

Both systems are fully reusable and designed to work in any Unreal project.

---

## Plugin Structure

```
AdvancedInteractionSystem/
 ├─ AdvancedInteractionSystem.uplugin
 ├─ Source/
 │   └─ AdvancedInteractionSystem/
 │       ├─ Public/
 │       │   ├─ Interactable.h
 │       │   ├─ InteractableComponent.h
 │       │   ├─ InteractionScannerComponent.h
 │       │   ├─ InteractionTypes.h
 │       │   ├─ InteractionSource.h
 │       │   ├─ InteractionBlueprintLibrary.h
 │       │   ├─ AdvancedInteractableComponent.h
 │       │   ├─ AdvancedInteractionScannerComponent.h
 │       │   ├─ AdvancedInteractionTypes.h
 │       └─ Private/
 │           ├─ *.cpp files
```

---

## Installation

1. Copy the plugin folder into
   `YourProject/Plugins/AdvancedInteractionSystem/`
2. Regenerate Visual Studio or Rider project files.
3. Build the project.
4. Enable the plugin in the Unreal Editor if needed.

---

## Minimal Usage

### 1. Add Scanner to Player

Attach `UInteractionScannerComponent` to your Character or PlayerController.

Example (C++):

```cpp
Scanner = CreateDefaultSubobject<UInteractionScannerComponent>("InteractionScanner");
```

Example (Blueprint):
Add the component from the Components panel.

### 2. Add InteractableComponent to Any Actor

Attach `UInteractableComponent` to an actor that should be interactable.

### 3. Bind Input

Call `Scanner->TryInteract(GetPawn())` on your Interact input.

---

## Advanced Usage

Use the extended components for AAA interactions.

### Add Advanced Components

* `UAdvancedInteractableComponent` on interactable actors
* `UAdvancedInteractionScannerComponent` on the player

### Input Handling

Call:

* `SetInteractInput(true)` on key press
* `SetInteractInput(false)` on key release

### Access Hold Progress

Use:

```
GetInteractionProgress()
```

to drive UI progress bars.

---

## Interaction Source Interface

To control where interaction traces originate, implement:

```cpp
UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
FVector GetInteractionViewLocation() const;

UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
FVector GetInteractionViewDirection() const;
```

These functions must return:

* The world position where interaction traces should start.
* The world direction the trace should point.

This interface can be implemented in Blueprint or C++.

---

## What You Should Implement in Blueprint

Implement the interface in your Character or PlayerController Blueprint.

### GetInteractionViewLocation

Return the camera location (or head/eye socket).

Blueprint implementation:

```
GetInteractionViewLocation → Camera Component → GetWorldLocation
```

If using a Character with a camera boom:

* `FollowCamera → GetWorldLocation()`
* or `FirstPersonCamera → GetWorldLocation()`

### GetInteractionViewDirection

Return the camera forward vector.

Blueprint implementation:

```
GetInteractionViewDirection → Camera Component → GetForwardVector
```

---

## Utility Functions

`InteractionBlueprintLibrary` exposes helper methods, including:

* `GetFirstInteractableComponent(AActor*)`
* `IsCloserInteraction(A, B)` for distance sorting

---

## Extending the Plugin

You can safely extend the system by:

* Adding new interaction types
* Adding cooldowns
* Adding replication wrappers
* Adding world subsystems for global management
* Adding UI widgets for prompts and hold progress

The plugin is designed to remain isolated from project-specific gameplay logic.

---
