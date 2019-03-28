## FrameLoadeType

```C++
#ifndef FrameLoaderTypes_h
#define FrameLoaderTypes_h

namespace blink {

// See WebFrameLoadType in public/web/WebFrameLoadType.h for details.
enum FrameLoadType {
  kFrameLoadTypeStandard,
  kFrameLoadTypeBackForward,
  kFrameLoadTypeReload,
  kFrameLoadTypeReplaceCurrentItem,
  kFrameLoadTypeInitialInChildFrame,
  kFrameLoadTypeInitialHistoryLoad,
  kFrameLoadTypeReloadBypassingCache,
};

enum NavigationType {
  kNavigationTypeLinkClicked,
  kNavigationTypeFormSubmitted,
  kNavigationTypeBackForward,
  kNavigationTypeReload,
  kNavigationTypeFormResubmitted,
  kNavigationTypeOther
};

enum ShouldSendReferrer { kMaybeSendReferrer, kNeverSendReferrer };

enum ShouldSetOpener { kMaybeSetOpener, kNeverSetOpener };

enum ReasonForCallingAllowPlugins {
  kAboutToInstantiatePlugin,
  kNotAboutToInstantiatePlugin
};

enum LoadStartType {
  kNavigationToDifferentDocument,
  kNavigationWithinSameDocument
};

enum SameDocumentNavigationSource {
  kSameDocumentNavigationDefault,
  kSameDocumentNavigationHistoryApi,
};

enum HistoryLoadType {
  kHistorySameDocumentLoad,
  kHistoryDifferentDocumentLoad
};

enum HistoryCommitType {
  kStandardCommit,
  kBackForwardCommit,
  kInitialCommitInChildFrame,
  kHistoryInertCommit
};

enum HistoryScrollRestorationType {
  kScrollRestorationAuto,
  kScrollRestorationManual
};

enum class ProgressBarCompletion {
  kLoadEvent,
  kResourcesBeforeDCL,
  kDOMContentLoaded,
  kResourcesBeforeDCLAndSameOriginIFrames
};

// This enum is used to index different kinds of single-page-application
// navigations for UMA enum histogram. New enum values can be added, but
// existing enums must never be renumbered or deleted and reused.
// This enum should be consistent with SinglePageAppNavigationType in
// tools/metrics/histograms/enums.xml.
enum SinglePageAppNavigationType {
  kSPANavTypeHistoryPushStateOrReplaceState = 0,
  kSPANavTypeSameDocumentBackwardOrForward = 1,
  kSPANavTypeOtherFragmentNavigation = 2,
  kSPANavTypeCount
};
}  // namespace blink

#endif

```

