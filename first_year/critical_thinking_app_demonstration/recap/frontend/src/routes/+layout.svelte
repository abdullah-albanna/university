<script lang="ts">
	import * as ModeWatcher from 'mode-watcher';
	import '../app.css';
	let { children } = $props();

	ModeWatcher.setMode('dark');
</script>

<ModeWatcher.ModeWatcher />
{@render children()}
