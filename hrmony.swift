import CoreGraphics

let eventMask =
    (1 << CGEventType.keyDown.rawValue) | (1 << CGEventType.keyUp.rawValue)
    | (1 << CGEventType.flagsChanged.rawValue)

var hrmMode: Bool = false
var hrmRemap: [CGKeyCode: CGEventFlags] = [12: CGEventFlags(rawValue: 1_048_848)]

func sendKeyPress(keyCode: CGKeyCode, flags: CGEventFlags) {
    if let keyDown = CGEvent(keyboardEventSource: nil, virtualKey: keyCode, keyDown: true) {
        keyDown.flags = flags
        keyDown.post(tap: .cgAnnotatedSessionEventTap)
    }

    if let keyUp = CGEvent(keyboardEventSource: nil, virtualKey: keyCode, keyDown: false) {
        keyUp.flags = flags
        keyUp.post(tap: .cgAnnotatedSessionEventTap)
    }
}

func processKeyPress(type: CGEventType, event: CGEvent) -> Unmanaged<CGEvent>? {
    if !hrmMode && type == .flagsChanged {
        let keyCode = event.flags.rawValue

        if keyCode == 1_048_848 || keyCode == 1_048_840 {
            hrmMode = true
            print("enter hrm mode")
        }
    }

    if hrmMode && type == .keyDown {
        hrmMode = false

        let keyCode: CGKeyCode = CGKeyCode(event.getIntegerValueField(.keyboardEventKeycode))
        if let flags = hrmRemap[keyCode] {
            sendKeyPress(keyCode: keyCode, flags: flags)
        }

        print("exit hrm mode")

        return nil
    }

    return Unmanaged.passUnretained(event)
}

guard
    let eventTap = CGEvent.tapCreate(
        tap: .cgSessionEventTap,
        place: .headInsertEventTap,
        options: .defaultTap,
        eventsOfInterest: CGEventMask(eventMask),
        callback: { (_, type, event, _) -> Unmanaged<CGEvent>? in
            return processKeyPress(type: type, event: event)
        },
        userInfo: nil
    )
else {
    fatalError("Failed to create event tap")
}

let runLoopSource = CFMachPortCreateRunLoopSource(kCFAllocatorDefault, eventTap, 0)
CFRunLoopAddSource(CFRunLoopGetCurrent(), runLoopSource, .commonModes)

CGEvent.tapEnable(tap: eventTap, enable: true)

CFRunLoopRun()
