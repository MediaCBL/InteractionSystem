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

## Passive Interaction

### Overview

`UPassiveInteractableComponent` provides **automatic proximity-based interaction feedback**.
When a player enters an interactable zone, a **Screen-space prompt widget** is shown and the player (or controller) is notified via an interface.

This system is fully C++ driven, **tick-free**, and intended for reusable interactable actors.

---

### Setup Instructions

1. **Add required components to the Interactable Actor**

   * A `UShapeComponent` (Sphere, Box, Capsule) used as the trigger zone
   * A `UWidgetComponent` configured as **World Space** (interaction prompt)
   * A `UPassiveInteractableComponent`

2. **Configure the Widget Component**

   * Assign a prompt widget class (key icon + text)
   * Set `Widget Space = Screen`
   * Position it above the actor (e.g. Z offset)

3. **Interaction Receiver**

   * Implement `InteractionReceiverInterface` on the **Pawn or PlayerController**
   * Handle `OnPassiveInteractableZoneChanged` to react to enter/exit events

---

### Runtime Behavior

* On overlap begin:

  * Prompt widget becomes visible
  * Player (or controller) is notified via `InteractionReceiverInterface`
* On overlap end:

  * Prompt widget is hidden
  * Exit notification is sent

Only **player-controlled pawns** trigger the system.

---

### Notes

* No ticking or polling is used
* Trigger and widget components are auto-discovered on `BeginPlay`
* Prompt display logic is fully actor-owned and multiplayer-safe

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
## License

MIT License

Copyright (c) 2025 MEDIA CBL

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in
all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
THE SOFTWARE.

---

